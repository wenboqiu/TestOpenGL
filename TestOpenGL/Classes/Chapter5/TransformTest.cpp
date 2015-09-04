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
//    ADD_TEST_CASE(SpritePolygonTest2);
//    ADD_TEST_CASE(SpritePolygonTest3);
//    ADD_TEST_CASE(SpritePolygonTest4);
//    ADD_TEST_CASE(SpritePolygonPerformanceTestStatic);
//    ADD_TEST_CASE(SpritePerformanceTestStatic);
//    ADD_TEST_CASE(SpritePolygonPerformanceTestDynamic);
//    ADD_TEST_CASE(SpritePerformanceTestDynamic);
}

void TransformTestCase::onBackCallback(cocos2d::Ref *sender)
{
    TestCase::onBackCallback(sender);
    Director::getInstance()->setClearColor(Color4F::BLACK);
}

TransformTest1::TransformTest1()
{
    _title = "Sample5_1";
    _subtitle = "test transform";
    
    auto star = Star::create();
    star->setPosition(VisibleRect::center());
    star->drawStar(100.0f, 50.0f);
    addChild(star);
}


