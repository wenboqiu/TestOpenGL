//
//  Cube.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/5/15.
//
//

#ifndef __TestOpenGL__Cube__
#define __TestOpenGL__Cube__

#include "cocos2d.h"
#include "../DrawNode3D.h"

class Cube : public cocos2d::DrawNode3D
{
public:
    CREATE_FUNC(Cube);
    /**
     * Draw 3D Line
     */
    void drawLine(const cocos2d::Vec3 &from, const cocos2d::Vec3 &to, const cocos2d::Color4F &color);
    
    /**
     * Draw 3D cube
     * @param point to a vertex array who has 8 element.
     *        vertices[0]:Left-top-front,
     *        vertices[1]:Left-bottom-front,
     *        vertices[2]:Right-bottom-front,
     *        vertices[3]:Right-top-front,
     *        vertices[4]:Right-top-back,
     *        vertices[5]:Right-bottom-back,
     *        vertices[6]:Left-bottom-back,
     *        vertices[7]:Left-top-back.
     * @param color
     */
    void drawCube(cocos2d::Vec3* vertices, const cocos2d::Color4F &color);
    
CC_CONSTRUCTOR_ACCESS:
    Cube();
    virtual ~Cube(){}
};

#endif /* defined(__TestOpenGL__Cube__) */
