//
//  Sample5_1.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/4/15.
//
//

#ifndef __TestOpenGL__Sample5_1__
#define __TestOpenGL__Sample5_1__

#include "../testBasic.h"
#include "../BaseTest.h"
#include "cocos2d.h"
DEFINE_TEST_SUITE(TransformTest);

class TransformTestCase : public TestCase
{
public:
    TransformTestCase();
    
protected:
    virtual void onBackCallback(Ref* sender);
    std::string _title;
    std::string _subtitle;
    virtual std::string title() const override {return _title;};
    virtual std::string subtitle() const override {return _subtitle;};
    cocos2d::Camera* _camera;
    
    
//    cocos2d::Node* _camControlNode;
//    cocos2d::Node* _camNode;
//    cocos2d::EventListenerTouchOneByOne* _lis;
};

class TransformTest1 : public TransformTestCase
{
public:
    CREATE_FUNC(TransformTest1);
    TransformTest1();
};

class TransformTest2 : public TransformTestCase
{
public:
    CREATE_FUNC(TransformTest2);
    TransformTest2();
};

#endif /* defined(__TestOpenGL__Sample5_1__) */
