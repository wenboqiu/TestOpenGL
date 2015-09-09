//
//  CustomSprite.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/9/15.
//
//

#ifndef __TestOpenGL__CustomSprite__
#define __TestOpenGL__CustomSprite__

#include "cocos2d.h"
#include "../DrawNode/DrawNode_VT.h"

class CustomSprite : public DrawNode_VT
{
public:
    CREATE_FUNC(CustomSprite);
    
    void setTexture(cocos2d::Texture2D *texture);
    void addImage(const std::string &filepath);
    void resetBuffer();
    void addVertex(V3F_T2F vertex);
    
    virtual void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    
CC_CONSTRUCTOR_ACCESS:
    CustomSprite();
    virtual ~CustomSprite();
    
protected:
    cocos2d::Texture2D* _texture;
};

#endif /* defined(__TestOpenGL__CustomSprite__) */
