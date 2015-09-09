//
//  TextureTest.cpp
//  TestOpenGL
//
//  Created by wenboqiu on 9/8/15.
//
//

#include "TextureTest.h"
#include "CustomSprite.h"
USING_NS_CC;

TextureTest::TextureTest()
{
    ADD_TEST_CASE(TextureTest1);
    ADD_TEST_CASE(TextureTest2);
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
    
    auto sprite = CustomSprite::create();
    sprite->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    sprite->loadShaderVertex("shaders/sample7_1.vert", "shaders/sample7_1.frag");
    
    sprite->resetBuffer();
    
    sprite->addVertex({Vec3(0.0f,100.0f,0.0f), Tex2F(0.5f, 0.0f)});
    sprite->addVertex({Vec3(-100.0f,-100.0f,0.0f), Tex2F(0.0f, 1.0f)});
    sprite->addVertex({Vec3(100.0f,-100.0f,0.0f), Tex2F(1.0f, 1.0f)});
    
    sprite->addImage("wall.png");
    
    addChild(sprite);
}

TextureTest2::TextureTest2()
{
    _title = "Sample7_2";
    _subtitle = "test texture wrapping";
    
    auto sprite = CustomSprite::create();
    sprite->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    sprite->loadShaderVertex("shaders/sample7_1.vert", "shaders/sample7_1.frag");
    
    sprite->resetBuffer();
    
    sprite->addVertex({Vec3(-100.0f,100.0f,0.0f), Tex2F(0.0f, 0.0f)});  //0
    sprite->addVertex({Vec3(100.0f,-100.0f,0.0f), Tex2F(2.0f, 2.0f)});  //2
    sprite->addVertex({Vec3(100.0f,100.0f,0.0f), Tex2F(2.0f, 0.0f)});   //1
    sprite->addVertex({Vec3(-100.0f,100.0f,0.0f), Tex2F(0.0f, 0.0f)});  //0
    sprite->addVertex({Vec3(-100.0f,-100.0f,0.0f), Tex2F(0.0f, 2.0f)}); //3
    sprite->addVertex({Vec3(100.0f,-100.0f,0.0f), Tex2F(2.0f, 2.0f)});  //2
    
    sprite->addImage("robot.png");
    
    addChild(sprite);
}
