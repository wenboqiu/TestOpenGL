//
//  Cube.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 9/5/15.
//
//

#include "Cube.h"
USING_NS_CC;

Cube::Cube()
{
//    _drawMode = GL_TRIANGLE_FAN;
}

bool Cube::init()
{
    if (!CustomDrawNode::init()) {
        return false;
    }
    
    _blendFunc = cocos2d::BlendFunc::ALPHA_PREMULTIPLIED;
    
    setGLProgramState(cocos2d::GLProgramState::getOrCreateWithGLProgramName(cocos2d::GLProgram::SHADER_NAME_POSITION_COLOR));
    
    //    ensureCapacity(512);
    
    if (cocos2d::Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        cocos2d::GL::bindVAO(_vao);
    }
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4B)* _bufferCapacity, _buffer, GL_STREAM_DRAW);
    
    glEnableVertexAttribArray(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B), (GLvoid *)0);
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B), (GLvoid *)offsetof(V3F_C4B, colors));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    if (cocos2d::Configuration::getInstance()->supportsShareableVAO())
    {
        cocos2d::GL::bindVAO(0);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    _dirty = true;
    
    return true;
}

void Cube::drawLine(const Vec3 &from, const Vec3 &to, const Color4F &color)
{
    unsigned int vertex_count = 2;
    ensureCapacity(vertex_count);
    
    Color4B col = Color4B(color);
    V3F_C4B a = {Vec3(from.x, from.y, from.z), col};
    V3F_C4B b = {Vec3(to.x, to.y, to.z), col, };
    
    V3F_C4B *lines = (V3F_C4B *)(_buffer + _bufferCount);
    lines[0] = a;
    lines[1] = b;
    
    _bufferCount += vertex_count;
    _dirty = true;
    
}

void Cube::drawCube(Vec3* vertices, const Color4F &color)
{
    // front face
    drawLine(vertices[0], vertices[1], color);
    drawLine(vertices[1], vertices[2], color);
    drawLine(vertices[2], vertices[3], color);
    drawLine(vertices[3], vertices[0], color);
    
    // back face
    drawLine(vertices[4], vertices[5], color);
    drawLine(vertices[5], vertices[6], color);
    drawLine(vertices[6], vertices[7], color);
    drawLine(vertices[7], vertices[4], color);
    
    // edge
    drawLine(vertices[0], vertices[7], color);
    drawLine(vertices[1], vertices[6], color);
    drawLine(vertices[2], vertices[5], color);
    drawLine(vertices[3], vertices[4], color);
}
