//
//  CustomSprite.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 9/9/15.
//
//

#include "CustomSprite.h"
USING_NS_CC;

CustomSprite::CustomSprite()
: _texture(nullptr)
{
    _drawMode = GL_TRIANGLES;
}

CustomSprite::~CustomSprite()
{
    CC_SAFE_RELEASE_NULL(_texture);
}

bool CustomSprite::init()
{
    if (!CustomDrawNode::init()) {
        return false;
    }
    
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_COLOR));
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
    }
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_T2F)* _bufferCapacity, _buffer, GL_STREAM_DRAW);
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_T2F), (GLvoid *)offsetof(V3F_T2F, vertices));
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_T2F), (GLvoid *)offsetof(V3F_T2F, texCoords));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(0);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    _dirty = true;

    return true;
}

void CustomSprite::setTexture(cocos2d::Texture2D *texture)
{
    CC_SAFE_RETAIN(texture);
    CC_SAFE_RELEASE(_texture);
    _texture = texture;
}

void CustomSprite::addImage(const std::string &filepath)
{
    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(filepath);
    setTexture(texture);
}

void CustomSprite::resetBuffer()
{
    clear();
    ensureCapacity(50);
}

void CustomSprite::addVertex(V3F_T2F vertex)
{
    ensureCapacity(1);
    
    _buffer[_bufferCount] = vertex;
    
    _bufferCount += 1;
    _dirty = true;
}

void CustomSprite::onDraw(const Mat4 &transform, uint32_t flags)
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
    
    if (_texture) {
        GL::bindTexture2D(_texture->getName());
    }
    
    glDrawArrays(_drawMode, 0, _bufferCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_bufferCount);
    glDisable(GL_DEPTH_TEST);
    CHECK_GL_ERROR_DEBUG();
}
