//
//  Widget.cpp
//  UICoordinate
//
//  Created by dzp on 14-7-15.
//
//

#include "Widget.h"
#include "HeaderFile.h"
USING_NS_CC;

Widget* Widget::getInstance()
{
    Widget *widget = new Widget();
    if(widget){
        widget->autorelease();
        return widget;
    }else{
        return NULL;
    }
}

float Widget::getConverNodeVec2ByX(cocos2d::Node *node)
{
    return node->getContentSize().width/2 + node->getPositionX();
}



unsigned long Widget::getCurrentTimemillisecond(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    unsigned long ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return ms;
}


bool Widget::isEqualVec1AndVec2(cocos2d::Vec2 v1, cocos2d::Vec2 v2)
{
    return (v1.x == v2.x && v1.y == v2.y);
}

