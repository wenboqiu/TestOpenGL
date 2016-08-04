//
//  LightTest.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/5/15.
//
//

#ifndef __TestOpenGL__LightTest__
#define __TestOpenGL__LightTest__

#include "testBasic.h"
#include "BaseTest.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

DEFINE_TEST_SUITE(LightTest);

class Ball;
class LightTestCase : public TestCase
{
public:
    LightTestCase();
    
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
    void updateLightLocation(int percent);
    
protected:
    virtual void onBackCallback(Ref* sender) override;
    std::string _title;
    std::string _subtitle;
    virtual std::string title() const override {return _title;};
    virtual std::string subtitle() const override {return _subtitle;};
    
    cocos2d::Camera* _camera;
    
    cocos2d::Node* _camControlNode;
    cocos2d::Node* _camNode;
    cocos2d::EventListenerTouchOneByOne* _lis;
    
    Ball* _ball;
};

class LightTest1 : public LightTestCase
{
public:
    CREATE_FUNC(LightTest1);
    LightTest1();
};

class LightTest2 : public LightTestCase
{
public:
    CREATE_FUNC(LightTest2);
    LightTest2();
};


class LightTest3 : public LightTestCase
{
public:
    CREATE_FUNC(LightTest3);
    LightTest3();
};

class LightTest4 : public LightTestCase
{
public:
    CREATE_FUNC(LightTest4);
    LightTest4();
};

class LightTest5 : public LightTestCase
{
public:
    CREATE_FUNC(LightTest5);
    LightTest5();
};

class LightTest9 : public LightTestCase
{
public:
    CREATE_FUNC(LightTest9);
    LightTest9();
};
#endif /* defined(__TestOpenGL__LightTest__) */
