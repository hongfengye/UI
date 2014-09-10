//
//  Widget.h
//  UICoordinate
//
//  Created by dzp on 14-7-15.
//
//

#ifndef __UICoordinate__Widget__
#define __UICoordinate__Widget__

#include <iostream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class Widget : public Ref{
public:
    static Widget* getInstance();
    
    float getConverNodeVec2ByX(Node* node);
    
    unsigned long getCurrentTimemillisecond();
    

    bool isEqualVec1AndVec2(Vec2 v1, Vec2 v2);
private:
    
    float middlePosX;
};

#endif /* defined(__UICoordinate__Widget__) */
