//
//  DrawNode_VC.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/8/15.
//
//

#ifndef __TestOpenGL__DrawNode_VC__
#define __TestOpenGL__DrawNode_VC__

#include "DrawNode3D.h"

class DrawNode_VC: public cocos2d::DrawNode3D
{
public:
    CREATE_FUNC(DrawNode_VC);
    
    virtual void reallocBuffer();
    
    virtual void onDraw(const cocos2d::Mat4& transform, uint32_t flags);

CC_CONSTRUCTOR_ACCESS:
    DrawNode_VC();
    virtual ~DrawNode_VC();
    virtual bool init() override;

protected:
    struct V3F_C4B
    {
        cocos2d::Vec3     vertices;
        cocos2d::Color4B  colors;
    };
    
    V3F_C4B*    _buffer;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(DrawNode_VC);
};

#endif /* defined(__TestOpenGL__DrawNode_VC__) */
