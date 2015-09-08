//
//  Star.h
//  TestOpenGL
//
//  Created by wenboqiu on 9/4/15.
//
//

#ifndef __TestOpenGL__Star__
#define __TestOpenGL__Star__

#include "cocos2d.h"
#include "../DrawNode/DrawNode_VC.h"

class Star : public DrawNode_VC
{
public:
    CREATE_FUNC(Star);
    void drawStar(float radiusOut, float radiusIn);
    
CC_CONSTRUCTOR_ACCESS:
    Star();
    virtual ~Star(){}
};

#endif /* defined(__TestOpenGL__Star__) */
