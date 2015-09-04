//
//  Sample5_1.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 9/4/15.
//
//

#include "TransformTest.h"
#include "../testResource.h"
#include "Star.h"

USING_NS_CC;

TransformTest::TransformTest()
{
    ADD_TEST_CASE(TransformTest1);
    ADD_TEST_CASE(TransformTest2);
//    ADD_TEST_CASE(SpritePolygonTest3);
//    ADD_TEST_CASE(SpritePolygonTest4);
//    ADD_TEST_CASE(SpritePolygonPerformanceTestStatic);
//    ADD_TEST_CASE(SpritePerformanceTestStatic);
//    ADD_TEST_CASE(SpritePolygonPerformanceTestDynamic);
//    ADD_TEST_CASE(SpritePerformanceTestDynamic);
}

TransformTestCase::TransformTestCase()
{
    /*
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
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_lis, this);
    */
}

void TransformTestCase::onBackCallback(cocos2d::Ref *sender)
{
    TestCase::onBackCallback(sender);
    Director::getInstance()->setClearColor(Color4F::BLACK);
}

TransformTest1::TransformTest1()
{
    _title = "Sample5_1";
    _subtitle = "test orthographic viewing";
    
    for (int i=0; i<5; ++i) {
        auto star = Star::create();
        star->setPosition(Vec2(VisibleRect::center().x+i*50, VisibleRect::center().y));
        star->setPositionZ(i*50);
        star->drawStar(100.0f, 50.0f);
        addChild(star);
    }
    
    auto size = Director::getInstance()->getWinSize();
    _camera = Camera::createOrthographic(size.width, size.height, -1024, 1024);
    _camera->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
    _camera->setRotation3D(Vec3(0.f, 0.f, 0.f));
    _camera->setCameraFlag(CameraFlag::USER1);
    
    addChild(_camera);
    setCameraMask(2);
}

TransformTest2::TransformTest2()
{
    _title = "Sample5_2";
    _subtitle = "test perspective viewing";
    
    for (int i=0; i<5; ++i) {
        auto star = Star::create();
        star->setPosition(Vec2(VisibleRect::center().x+i*50, VisibleRect::center().y));
        star->setPositionZ(i*50);
        star->drawStar(100.0f, 50.0f);
        addChild(star);
    }
    
    auto size = Director::getInstance()->getWinSize();
    float zeye = Director::getInstance()->getZEye();
    _camera = Camera::createPerspective(60, (GLfloat)size.width / size.height, 10, zeye + size.height / 2.0f);
    _camera->setPosition3D(Vec3(size.width/2, size.height/2.0f, zeye));
    _camera->setRotation3D(Vec3(0,0,0));
    _camera->setCameraFlag(CameraFlag::USER1);
    
    addChild(_camera);
    setCameraMask(2);
}

