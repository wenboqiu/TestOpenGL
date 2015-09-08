//
//  DrawNode_VT.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/8/15.
//
//

#ifndef __TestOpenGL__DrawNode_VT__
#define __TestOpenGL__DrawNode_VT__

#include "DrawNode3D.h"

class DrawNode_VT: public cocos2d::DrawNode3D
{
public:
    CREATE_FUNC(DrawNode_VT);
    
    virtual void reallocBuffer();
    
    virtual void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    
CC_CONSTRUCTOR_ACCESS:
    DrawNode_VT();
    virtual ~DrawNode_VT();
    virtual bool init() override;
    
protected:
    struct V3F_T2F
    {
        cocos2d::Vec3     vertices;
        cocos2d::Tex2F    texCoords;
    };
    
    V3F_T2F*    _buffer;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(DrawNode_VT);
};

#endif /* defined(__TestOpenGL__DrawNode_VT__) */
