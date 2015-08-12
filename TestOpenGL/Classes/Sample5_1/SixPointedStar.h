//
//  SixPointedStar.h
//  TestOpenGL
//
//  Created by wenboqiu on 8/12/15.
//
//

#ifndef __TestOpenGL__SixPointedStar__
#define __TestOpenGL__SixPointedStar__

#include "cocos2d.h"

class SixPointedStar : public cocos2d::Node
{
public:
    CREATE_FUNC(SixPointedStar);
    
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    
    virtual void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
    
    void ensureCapacity(int count);
    
    void initVertexData(float radiusOut, float radiusIn);
    
CC_CONSTRUCTOR_ACCESS:
    SixPointedStar();
    
    virtual ~SixPointedStar();
    
    virtual bool init() override;
    
private:
    struct V3F_C4B
    {
        cocos2d::Vec3     vertices;
        cocos2d::Color4B  colors;
    };
    
    GLuint      _vao;
    GLuint      _vbo;
    
    int         _bufferCapacity;
    GLsizei     _bufferCount;
    
    V3F_C4B*    _buffer;
    
    cocos2d::BlendFunc   _blendFunc;
    
    cocos2d::CustomCommand _customCommand;
    
    bool        _dirty;
    
};
#endif /* defined(__TestOpenGL__SixPointedStar__) */
