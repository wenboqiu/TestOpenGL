//
//  Triangle.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 9/8/15.
//
//

#include "Triangle.h"
USING_NS_CC;

Triangle::Triangle()
{
    _drawMode = GL_TRIANGLES;
    _textureWall = Director::getInstance()->getTextureCache()->addImage("wall.png");
    CC_SAFE_RETAIN(_textureWall);
}

Triangle::~Triangle()
{
    CC_SAFE_RELEASE_NULL(_textureWall);
}

void Triangle::drawTriangle()
{
    clear();
    ensureCapacity(3);
    
    _buffer[0] = {Vec3(0.0f,100.0f,0.0f), Tex2F(0.5f, 0.0f)};
    _buffer[1] = {Vec3(-100.0f,-100.0f,0.0f), Tex2F(0.0f, 1.0f)};
    _buffer[2] = {Vec3(100.0f,-100.0f,0.0f), Tex2F(1.0f, 1.0f)};
    
    _bufferCount += 3;
    _dirty = true;
}

void Triangle::onDraw(const Mat4 &transform, uint32_t flags)
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
    
    GL::bindTexture2D(_textureWall->getName());
    
    glDrawArrays(_drawMode, 0, _bufferCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_bufferCount);
    glDisable(GL_DEPTH_TEST);
    CHECK_GL_ERROR_DEBUG();
}