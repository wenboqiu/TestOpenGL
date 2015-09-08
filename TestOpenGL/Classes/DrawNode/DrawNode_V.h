//
//  DrawNode_V.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/8/15.
//
//

#ifndef __TestOpenGL__DrawNode_V__
#define __TestOpenGL__DrawNode_V__

#include "DrawNode3D.h"

class DrawNode_V: public cocos2d::DrawNode3D
{
public:
    CREATE_FUNC(DrawNode_V);
    
    virtual void reallocBuffer();
    
    virtual void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    
CC_CONSTRUCTOR_ACCESS:
    DrawNode_V();
    virtual ~DrawNode_V();
    virtual bool init() override;
    
protected:
    cocos2d::Vec3*    _buffer;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(DrawNode_V);
};

#endif /* defined(__TestOpenGL__DrawNode_V__) */
