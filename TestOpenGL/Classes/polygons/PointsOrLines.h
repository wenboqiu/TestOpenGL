//
//  PointsOrLines.hpp
//  TestOpenGL
//
//  Created by wenboqiu on 8/13/16.
//
//

#ifndef __TestOpenGL__PointsOrLines__
#define __TestOpenGL__PointsOrLines__

#include "cocos2d.h"
#include "CustomDrawNode.h"
#include "customTypes.h"

class PointsOrLines : public CustomDrawNode<class V3F_C4B>
{
public:
    CREATE_FUNC(PointsOrLines);
    virtual bool init();
    void drawPointsOrLines(cocos2d::Vec3* vertices, unsigned int count, const cocos2d::Color4F &color);
    
CC_CONSTRUCTOR_ACCESS:
    PointsOrLines();
    virtual ~PointsOrLines(){}
};

#endif /* __TestOpenGL__PointsOrLines__ */
