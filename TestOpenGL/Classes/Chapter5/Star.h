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
#include "../DrawNode3D.h"

class Star : public cocos2d::DrawNode3D
{
public:
    CREATE_FUNC(Star);
    void drawStar(float radiusOut, float radiusIn);
};

#endif /* defined(__TestOpenGL__Star__) */
