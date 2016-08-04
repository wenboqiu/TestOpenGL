//
//  LightTest.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 9/5/15.
//
//

#include "LightTest.h"
#include "Ball.h"

USING_NS_CC;
using namespace cocos2d::ui;

LightTest::LightTest()
{
    ADD_TEST_CASE(LightTest1);
    ADD_TEST_CASE(LightTest2);
    ADD_TEST_CASE(LightTest3);
    ADD_TEST_CASE(LightTest4);
    ADD_TEST_CASE(LightTest5);
    ADD_TEST_CASE(LightTest9);
}

LightTestCase::LightTestCase()
{
    auto s = Director::getInstance()->getWinSize();
    
    _camControlNode = Node::create();
    _camControlNode->setNormalizedPosition(Vec2(.5,.5));
    addChild(_camControlNode);
    
    _camNode = Node::create();
    _camNode->setPositionZ(Camera::getDefaultCamera()->getPosition3D().z);
    _camControlNode->addChild(_camNode);
    
    //Listener
    _lis = EventListenerTouchOneByOne::create();
    _lis->onTouchBegan = [this](Touch* t, Event* e) {
        return true;
    };
    
    _lis->onTouchMoved = [this](Touch* t, Event* e) {
        float dx = t->getDelta().x;
        Vec3 rot = _camControlNode->getRotation3D();
        rot.y += dx;
        _camControlNode->setRotation3D(rot);
        
        Vec3 worldPos;
        _camNode->getNodeToWorldTransform().getTranslation(&worldPos);
        
        Camera::getDefaultCamera()->setPosition3D(worldPos);
        Camera::getDefaultCamera()->lookAt(_camControlNode->getPosition3D());
        
        _ball->setCameraLocaiton(worldPos);
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_lis, this);
}

void LightTestCase::onBackCallback(cocos2d::Ref *sender)
{
    TestCase::onBackCallback(sender);
    Director::getInstance()->setClearColor(Color4F::BLACK);
}

void LightTestCase::sliderEvent(Ref *pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        updateLightLocation(slider->getPercent());
    }
}

void LightTestCase::updateLightLocation(int percent)
{
    auto s = Director::getInstance()->getWinSize();
    float newX = s.width * percent / 100;
    _ball->setLightLocaiton(Vec3(newX, s.height/2, 300.0f));
}

LightTest1::LightTest1()
{
    _title = "Sample6_1";
    _subtitle = "test sphere";
    
    auto ball = Ball::create();
    ball->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    ball->loadShaderVertex("shaders/sample6_1.vert", "shaders/sample6_1.frag");
    ball->drawSphere(200.0f);
    addChild(ball);
}

LightTest2::LightTest2()
{
    _title = "Sample6_2";
    _subtitle = "test ambient";
    
    auto ball = Ball::create();
    ball->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    ball->loadShaderVertex("shaders/sample6_2.vert", "shaders/sample6_2.frag");
    ball->drawSphere(200.0f);
    addChild(ball);
}

LightTest3::LightTest3()
{
    _title = "Sample6_3";
    _subtitle = "test diffuse";
    
    _ball = Ball::create();
    _ball->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    _ball->loadShaderVertex("shaders/sample6_3.vert", "shaders/sample6_3.frag");
    _ball->drawSphere(200.0f);
    addChild(_ball);
    
    auto* slider = Slider::create();
    slider->loadBarTexture("sliderTrack.png");
    slider->loadSlidBallTextures("sliderThumb.png");
    slider->setPosition(Vec2(VisibleRect::center().x, VisibleRect::top().y - 100));
    slider->addEventListener(CC_CALLBACK_2(LightTest3::sliderEvent, this));
    addChild(slider);
    
    updateLightLocation(slider->getPercent());
}

LightTest4::LightTest4()
{
    _title = "Sample6_4";
    _subtitle = "test specular";
    
    _ball = Ball::create();
    _ball->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    _ball->loadShaderVertex("shaders/sample6_4.vert", "shaders/sample6_4.frag");
    _ball->drawSphere(200.0f);
    addChild(_ball);
    
    auto* slider = Slider::create();
    slider->loadBarTexture("sliderTrack.png");
    slider->loadSlidBallTextures("sliderThumb.png");
    slider->setPosition(Vec2(VisibleRect::center().x, VisibleRect::top().y - 100));
    slider->addEventListener(CC_CALLBACK_2(LightTest4::sliderEvent, this));
    addChild(slider);
    
    updateLightLocation(slider->getPercent());
    _ball->setCameraLocaiton(Camera::getDefaultCamera()->getPosition3D());
}

LightTest5::LightTest5()
{
    _title = "Sample6_5";
    _subtitle = "test combine (per vert lighting)";
    
    _ball = Ball::create();
    _ball->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    _ball->loadShaderVertex("shaders/sample6_5.vert", "shaders/sample6_5.frag");
    _ball->drawSphere(200.0f);
    addChild(_ball);
    
    auto* slider = Slider::create();
    slider->loadBarTexture("sliderTrack.png");
    slider->loadSlidBallTextures("sliderThumb.png");
    slider->setPosition(Vec2(VisibleRect::center().x, VisibleRect::top().y - 100));
    slider->addEventListener(CC_CALLBACK_2(LightTest4::sliderEvent, this));
    addChild(slider);
    
    updateLightLocation(slider->getPercent());
    _ball->setCameraLocaiton(Camera::getDefaultCamera()->getPosition3D());

}

LightTest9::LightTest9()
{
    _title = "Sample6_9";
    _subtitle = "test per frag lighting";
    
    _ball = Ball::create();
    _ball->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    _ball->loadShaderVertex("shaders/sample6_9.vert", "shaders/sample6_9.frag");
    _ball->drawSphere(200.0f);
    addChild(_ball);
    
    auto* slider = Slider::create();
    slider->loadBarTexture("sliderTrack.png");
    slider->loadSlidBallTextures("sliderThumb.png");
    slider->setPosition(Vec2(VisibleRect::center().x, VisibleRect::top().y - 100));
    slider->addEventListener(CC_CALLBACK_2(LightTest4::sliderEvent, this));
    addChild(slider);
    
    updateLightLocation(slider->getPercent());
    _ball->setCameraLocaiton(Camera::getDefaultCamera()->getPosition3D());
    
}
