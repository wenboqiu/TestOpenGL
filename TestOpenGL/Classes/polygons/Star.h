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
#include "CustomDrawNode.h"
#include "customTypes.h"

class Star : public CustomDrawNode<class V3F_C4B>
{
public:
    CREATE_FUNC(Star);
    virtual bool init();
    void drawStar(float radiusOut, float radiusIn);
    
CC_CONSTRUCTOR_ACCESS:
    Star();
    virtual ~Star(){}
};

#endif /* defined(__TestOpenGL__Star__) */
