//
//  TextureTest.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 9/8/15.
//
//

#include "TextureTest.h"
#include "Triangle.h"
USING_NS_CC;

TextureTest::TextureTest()
{
    ADD_TEST_CASE(TextureTest1);
//    ADD_TEST_CASE(TextureTest2);
//    ADD_TEST_CASE(TextureTest3);
//    ADD_TEST_CASE(TextureTest4);
//    ADD_TEST_CASE(TextureTest5);
//    ADD_TEST_CASE(TextureTest9);
}

TextureTestCase::TextureTestCase()
{
}

void TextureTestCase::onBackCallback(cocos2d::Ref *sender)
{
    TestCase::onBackCallback(sender);
    Director::getInstance()->setClearColor(Color4F::BLACK);
}

TextureTest1::TextureTest1()
{
    _title = "Sample7_1";
    _subtitle = "test texture mapping";
    
    auto ball = Triangle::create();
    ball->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    ball->loadShaderVertex("shaders/sample7_1.vert", "shaders/sample7_1.frag");
    ball->drawTriangle();
    addChild(ball);
}
