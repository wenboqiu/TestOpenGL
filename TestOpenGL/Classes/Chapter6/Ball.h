//
//  Ball.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/5/15.
//
//

#ifndef __TestOpenGL__Ball__
#define __TestOpenGL__Ball__

#include "cocos2d.h"
#include "../DrawNode3D.h"

class Ball : public cocos2d::DrawNode3D
{
public:
    CREATE_FUNC(Ball);
    
    void drawSphere(float radius);
    virtual void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    
    inline void setLightLocaiton(cocos2d::Vec3 location){ _lightLocation = location; }
    
    inline void setCameraLocaiton(cocos2d::Vec3 location){ _cameraLocation = location; }
    
CC_CONSTRUCTOR_ACCESS:
    Ball();
    virtual ~Ball(){}
    
protected:
    float _radius;
    cocos2d::Vec3 _lightLocation;
    cocos2d::Vec3 _cameraLocation;
};

#endif /* defined(__TestOpenGL__Ball__) */
