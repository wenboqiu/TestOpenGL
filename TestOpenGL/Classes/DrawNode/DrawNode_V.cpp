//
//  DrawNode_V.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 9/8/15.
//
//

#include "DrawNode_V.h"
USING_NS_CC;

DrawNode_V::DrawNode_V()
: _buffer(nullptr)
{
}

DrawNode_V::~DrawNode_V()
{
    free(_buffer);
    _buffer = nullptr;
}

void DrawNode_V::reallocBuffer()
{
    _buffer = (Vec3*)realloc(_buffer, _bufferCapacity*sizeof(Vec3));
}

bool DrawNode_V::init()
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_COLOR));
    
    ensureCapacity(512);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
    }
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3)* _bufferCapacity, _buffer, GL_STREAM_DRAW);
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (GLvoid *)0);
    
//    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B), (GLvoid *)offsetof(V3F_C4B, colors));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(0);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    _dirty = true;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Need to listen the event only when not use batchnode, because it will use VBO
    auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
        /** listen the event that coming to foreground on Android */
        this->init();
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
    
    return true;
}

void DrawNode_V::onDraw(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    glEnable(GL_DEPTH_TEST);
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);
    
    if (_dirty)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3)*_bufferCapacity, _buffer, GL_STREAM_DRAW);
        _dirty = false;
    }
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(_vao);
    }
    
    glDrawArrays(_drawMode, 0, _bufferCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_bufferCount);
    glDisable(GL_DEPTH_TEST);
    CHECK_GL_ERROR_DEBUG();
}
