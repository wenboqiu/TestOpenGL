//
//  Sample5_1.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/4/15.
//
//

#ifndef __TestOpenGL__TransformTest__
#define __TestOpenGL__TransformTest__

#include "testBasic.h"
#include "BaseTest.h"
#include "cocos2d.h"
DEFINE_TEST_SUITE(TransformTest);

class TransformTestCase : public TestCase
{
public:
    TransformTestCase();
    
protected:
    virtual void onBackCallback(Ref* sender) override;
    std::string _title;
    std::string _subtitle;
    virtual std::string title() const override {return _title;};
    virtual std::string subtitle() const override {return _subtitle;};
    cocos2d::Camera* _camera;
    
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

class TransformTest3 : public TransformTestCase
{
public:
    CREATE_FUNC(TransformTest3);
    TransformTest3();
    
protected:
    cocos2d::OBB _obbt;
    
    cocos2d::Node* _camControlNode;
    cocos2d::Node* _camNode;
    cocos2d::EventListenerTouchOneByOne* _lis;
};

#endif /* defined(__TestOpenGL__TransformTest__) */
