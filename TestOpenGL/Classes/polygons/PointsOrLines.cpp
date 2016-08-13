//
//  PointsOrLines.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 8/13/16.
//
//

#include "PointsOrLines.h"

USING_NS_CC;

PointsOrLines::PointsOrLines()
{
    _drawMode = GL_POINTS;
}

bool PointsOrLines::init()
{
    if (!CustomDrawNode::init()) {
        return false;
    }
    
    _blendFunc = cocos2d::BlendFunc::ALPHA_PREMULTIPLIED;
    
    setGLProgramState(cocos2d::GLProgramState::getOrCreateWithGLProgramName(cocos2d::GLProgram::SHADER_NAME_POSITION_COLOR));
    
    if (cocos2d::Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        cocos2d::GL::bindVAO(_vao);
    }
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    
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

void PointsOrLines::drawPointsOrLines(Vec3* vertices, unsigned int count, const Color4F &color)
{
    _bufferCount = 0;
    ensureCapacity(count);
    _bufferCount = count;
    
    Color4B col = Color4B(color);
    
    for (int i=0; i<count; ++i) {
        _buffer[i] = {vertices[i], col};
    }
    
    _dirty = true;
}
