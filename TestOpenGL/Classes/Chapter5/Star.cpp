//
//  Star.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 9/4/15.
//
//

#include "Star.h"
USING_NS_CC;

void Star::drawStar(float radiusOut, float radiusIn)
{
    clear();
    ensureCapacity(50);
    
    float tempAngle = 360/6;

    int vIndex = 0;
    
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