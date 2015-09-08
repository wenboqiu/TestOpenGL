//
//  Triangle.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/8/15.
//
//

#ifndef __TestOpenGL__Triangle__
#define __TestOpenGL__Triangle__

#include "cocos2d.h"
#include "../DrawNode/DrawNode_VT.h"

class Triangle : public DrawNode_VT
{
public:
    CREATE_FUNC(Triangle);
    
    void drawTriangle();
    virtual void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    
CC_CONSTRUCTOR_ACCESS:
    Triangle();
    virtual ~Triangle();
    
protected:
    cocos2d::Texture2D* _textureWall;
};

#endif /* defined(__TestOpenGL__Triangle__) */
