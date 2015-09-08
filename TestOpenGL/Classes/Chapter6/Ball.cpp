//
//  Ball.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 9/5/15.
//
//

#include "Ball.h"
USING_NS_CC;

Ball::Ball()
{
    _drawMode = GL_TRIANGLES;
}

void Ball::drawSphere(float radius)
{
    clear();
    
    _radius = radius;
    
    int angleSpan = 10;
    int vCount = (180/angleSpan)*(360/angleSpan)*6;
    ensureCapacity(vCount);
        
    int vIndex = 0;
    
    for (int vAngle = 90; vAngle >-90; vAngle -= angleSpan) {
        for (int hAngle = 360; hAngle > 0; hAngle -= angleSpan) {
            float x0 = radius * cosf(CC_DEGREES_TO_RADIANS(vAngle)) * cosf(CC_DEGREES_TO_RADIANS(hAngle));
            float y0 = radius * cosf(CC_DEGREES_TO_RADIANS(vAngle)) * sinf(CC_DEGREES_TO_RADIANS(hAngle));
            float z0 = radius * sinf(CC_DEGREES_TO_RADIANS(vAngle));
            
            float x1 = radius * cosf(CC_DEGREES_TO_RADIANS(vAngle-angleSpan)) * cosf(CC_DEGREES_TO_RADIANS(hAngle));
            float y1 = radius * cosf(CC_DEGREES_TO_RADIANS(vAngle-angleSpan)) * sinf(CC_DEGREES_TO_RADIANS(hAngle));
            float z1 = radius * sinf(CC_DEGREES_TO_RADIANS(vAngle-angleSpan));
            
            float x2 = radius * cosf(CC_DEGREES_TO_RADIANS(vAngle-angleSpan)) * cosf(CC_DEGREES_TO_RADIANS(hAngle-angleSpan));
            float y2 = radius * cosf(CC_DEGREES_TO_RADIANS(vAngle-angleSpan)) * sinf(CC_DEGREES_TO_RADIANS(hAngle-angleSpan));
            float z2 = radius * sinf(CC_DEGREES_TO_RADIANS(vAngle-angleSpan));
            
            float x3 = radius * cosf(CC_DEGREES_TO_RADIANS(vAngle)) * cosf(CC_DEGREES_TO_RADIANS(hAngle-angleSpan));
            float y3 = radius * cosf(CC_DEGREES_TO_RADIANS(vAngle)) * sinf(CC_DEGREES_TO_RADIANS(hAngle-angleSpan));
            float z3 = radius * sinf(CC_DEGREES_TO_RADIANS(vAngle));

            _buffer[vIndex*6+0] = Vec3(x1, y1, z1);
            _buffer[vIndex*6+1] = Vec3(x0, y0, z0);
            _buffer[vIndex*6+2] = Vec3(x3, y3, z3);
            _buffer[vIndex*6+3] = Vec3(x1, y1, z1);
            _buffer[vIndex*6+4] = Vec3(x3, y3, z3);
            _buffer[vIndex*6+5] = Vec3(x2, y2, z2);
            
            vIndex++;
        }
    }
    
    _bufferCount += vCount;
    _dirty = true;
}

void Ball::onDraw(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    
    glEnable(GL_CULL_FACE);
//    glCullFace(GL_FRONT);
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
    
    GLint location1 = glProgram->getUniformLocation("u_radius");
    glProgram->setUniformLocationWith1f(location1, _radius);
    
    GLint location2 = glProgram->getUniformLocation("u_lightLocation");
    glProgram->setUniformLocationWith3f(location2, _lightLocation.x, _lightLocation.y, _lightLocation.z);
    
    GLint location3 = glProgram->getUniformLocation("u_camera");
    glProgram->setUniformLocationWith3f(location3, _cameraLocation.x, _cameraLocation.y, _cameraLocation.z);
    
    glDrawArrays(_drawMode, 0, _bufferCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_bufferCount);
    glDisable(GL_DEPTH_TEST);
//    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);
    CHECK_GL_ERROR_DEBUG();
}