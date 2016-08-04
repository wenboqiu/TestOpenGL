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
#include "CustomDrawNode.h"

class CustomSprite : public CustomDrawNode<cocos2d::V3F_T2F>
{
public:
    CREATE_FUNC(CustomSprite);
    virtual bool init();
    
    void setTexture(cocos2d::Texture2D *texture);
    void addImage(const std::string &filepath);
    void resetBuffer();
    void addVertex(cocos2d::V3F_T2F vertex);
    
    virtual void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
    
CC_CONSTRUCTOR_ACCESS:
    CustomSprite();
    virtual ~CustomSprite();
    
protected:
    cocos2d::Texture2D* _texture;
};

#endif /* defined(__TestOpenGL__CustomSprite__) */
