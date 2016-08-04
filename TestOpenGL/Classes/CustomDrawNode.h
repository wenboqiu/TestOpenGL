//
//  CustomDrawNode.h
//  TestOpenGL
//
//  Created by wenboqiu on 8/3/16.
//
//

#ifndef CustomDrawNode_h
#define CustomDrawNode_h

#include "cocos2d.h"
#include "DrawNode3D.h"

template <class Type>
class CustomDrawNode: public cocos2d::DrawNode3D
{
public:
    CREATE_FUNC(CustomDrawNode);
    
    virtual void reallocBuffer() override;
    
    virtual void onDraw(const cocos2d::Mat4& transform, uint32_t flags) override;
    
CC_CONSTRUCTOR_ACCESS:
    CustomDrawNode();
    virtual ~CustomDrawNode();
    virtual bool init() override;
    
protected:
    Type*    _buffer;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(CustomDrawNode);
};

template <class Type>
CustomDrawNode<Type>::CustomDrawNode()
: _buffer(nullptr)
{
}

template <class Type>
CustomDrawNode<Type>::~CustomDrawNode()
{
    free(_buffer);
    _buffer = nullptr;
}

template <class Type>
void CustomDrawNode<Type>::reallocBuffer()
{
    _buffer = (Type*)realloc(_buffer, _bufferCapacity*sizeof(Type));
}

template <class Type>
bool CustomDrawNode<Type>::init()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Need to listen the event only when not use batchnode, because it will use VBO
    auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
        /** listen the event that coming to foreground on Android */
        this->init();
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
    
    return true;
}

template <class Type>
void CustomDrawNode<Type>::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    glEnable(GL_DEPTH_TEST);
    cocos2d::GL::blendFunc(_blendFunc.src, _blendFunc.dst);
    
    if (_dirty)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Type)*_bufferCapacity, _buffer, GL_STREAM_DRAW);
        _dirty = false;
    }
    
    if (cocos2d::Configuration::getInstance()->supportsShareableVAO())
    {
        cocos2d::GL::bindVAO(_vao);
    }
    
    glDrawArrays(_drawMode, 0, _bufferCount);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    if (cocos2d::Configuration::getInstance()->supportsShareableVAO())
    {
        cocos2d::GL::bindVAO(0);
    }
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_bufferCount);
    glDisable(GL_DEPTH_TEST);
    CHECK_GL_ERROR_DEBUG();
}

#endif /* CustomDrawNode_h */
