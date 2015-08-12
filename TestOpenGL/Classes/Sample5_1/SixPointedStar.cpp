//
//  SixPointedStar.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 8/12/15.
//
//

#include "SixPointedStar.h"

USING_NS_CC;

SixPointedStar::SixPointedStar()
: _vao(0)
, _vbo(0)
, _bufferCapacity(0)
, _bufferCount(0)
, _buffer(nullptr)
, _dirty(false)
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
}

SixPointedStar::~SixPointedStar()
{
    free(_buffer);
    _buffer = nullptr;
    
    glDeleteBuffers(1, &_vbo);
    _vbo = 0;
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glDeleteVertexArrays(1, &_vao);
        GL::bindVAO(0);
        _vao = 0;
    }
    
}

bool SixPointedStar::init()
{
    if (!Node::init()) {
        return false;
    }
    
    initVertexData(100.0f, 50.0f);
    
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_COLOR));
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
    }
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4B)* _bufferCapacity, _buffer, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B), (GLvoid *)offsetof(V3F_C4B, vertices));
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B), (GLvoid *)offsetof(V3F_C4B, colors));
    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, 1.0f, 1.0f, 1.0f, 1.0f);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(0);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    _dirty = true;
    
    
    return true;
}

void SixPointedStar::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(SixPointedStar::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void SixPointedStar::onDraw(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(_vao);
    }
    
    glDrawArrays(GL_TRIANGLES, 0, _bufferCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_bufferCount);
    
    CHECK_GL_ERROR_DEBUG();
}

void SixPointedStar::ensureCapacity(int count)
{
    CCASSERT(count>=0, "capacity must be >= 0");
    
    if(_bufferCount + count > _bufferCapacity)
    {
        _bufferCapacity += MAX(_bufferCapacity, count);
        _buffer = (V3F_C4B*)realloc(_buffer, _bufferCapacity*sizeof(V3F_C4B));
    }
}

void SixPointedStar::initVertexData(float radiusOut, float radiusIn)
{
    float tempAngle = 360/6;
    
    int vIndex = 0;
    
    ensureCapacity(50);
    
    for (float angle = 0; angle < 360; angle += tempAngle) {
        Vec3 p0 = Vec3(0.0f,0.0f,0.0f);
        
        Vec3 p1;
        p1.x = radiusOut * cosf(CC_DEGREES_TO_RADIANS(angle));
        p1.y = radiusOut * sinf(CC_DEGREES_TO_RADIANS(angle));
        p1.z = 0.0f;
        
        Vec3 p2;
        p2.x = radiusIn * cosf(CC_DEGREES_TO_RADIANS(angle+tempAngle/2));
        p2.y = radiusIn * sinf(CC_DEGREES_TO_RADIANS(angle+tempAngle/2));
        p2.z = 0.0f;
        
        
        Vec3 p3 = Vec3(0.0f,0.0f,0.0f);
        
        Vec3 p4;
        p4.x = radiusIn * cosf(CC_DEGREES_TO_RADIANS(angle+tempAngle/2));
        p4.y = radiusIn * sinf(CC_DEGREES_TO_RADIANS(angle+tempAngle/2));
        p4.z = 0.0f;
        
        Vec3 p5;
        p5.x = radiusOut * cosf(CC_DEGREES_TO_RADIANS(angle+tempAngle));
        p5.y = radiusOut * sinf(CC_DEGREES_TO_RADIANS(angle+tempAngle));
        p5.z = 0.0f;
        
        _buffer[vIndex*6+0] = {p0, Color4B(255, 255, 255, 255)};
        _buffer[vIndex*6+1] = {p1, Color4B(255, 0, 0, 255)};
        _buffer[vIndex*6+2] = {p2, Color4B(0, 255, 0, 255)};
        _buffer[vIndex*6+3] = {p3, Color4B(255, 255, 255, 255)};
        _buffer[vIndex*6+4] = {p4, Color4B(0, 255, 0, 255)};
        _buffer[vIndex*6+5] = {p5, Color4B(255, 0, 0, 255)};
            
        vIndex++;
    }
    
    _bufferCount += vIndex*6;
    _dirty = true;
}
