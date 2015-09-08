//
//  TextureTest.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/8/15.
//
//

#ifndef __TestOpenGL__TextureTest__
#define __TestOpenGL__TextureTest__

#include "../testBasic.h"
#include "../BaseTest.h"
#include "cocos2d.h"

DEFINE_TEST_SUITE(TextureTest);

class TextureTestCase : public TestCase
{
public:
    TextureTestCase();
    
protected:
    virtual void onBackCallback(Ref* sender);
    std::string _title;
    std::string _subtitle;
    virtual std::string title() const override {return _title;};
    virtual std::string subtitle() const override {return _subtitle;};
};

class TextureTest1 : public TextureTestCase
{
public:
    CREATE_FUNC(TextureTest1);
    TextureTest1();
};

#endif /* defined(__TestOpenGL__TextureTest__) */
