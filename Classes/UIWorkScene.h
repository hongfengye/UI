//
//  UIWorkScene.h
//  UI
//
//  Created by dzp on 14-7-16.
//
//

#ifndef __UI__UIWorkScene__
#define __UI__UIWorkScene__

#include <iostream>
#include "cocos2d.h"
#include "Widget.h"
#include "extensions/cocos-ext.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class UIWorkScene : public cocos2d::Layer
{
public:
    enum PanelType{
        exit = 1,
        save =2
    };
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static UIWorkScene* createLayer(bool isDebug,string imageName,float x,float y,int w,int h);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    void initWith(bool isDebug,string imageName,float x,float y,int w,int h);
    
    // a selector callback
    void menuCallback(cocos2d::Ref* pSender);
    
private:

    /**
     以设置的坐标点为中心，转化后的坐标，参数：硬坐标
     **/
    Vec2 converLationinView(float cursorX, float cursorY);
    
    /**
     按设置的比率转化为所需的实际坐标，参数：硬坐标
     **/
    Vec2 converOpenglRate(Vec2 cursor);
    
    /**
     更新当前坐标，参数：当前对象
     **/
    Sprite* addCoordinate(Vec2 v);
    
    /**
     更新Debug模式的坐标，参数：转化后的坐标
     **/
    void updateCoordinate(Sprite* sprite);
    
    /**
     创建面板，参数：类型
     **/
    Sprite* createPanel(PanelType panelType);
    
    /**
     退出回调
     **/
    void exitCallBack(Ref* sender);
    
    /**
     保存回调
     **/
    void saveCallBack(Ref* sender);
    
    /**
     取消回调
     **/
    void cancelCallBack(Ref* sender);
    
    /**
     更新Debug模式的坐标，参数：转化后的坐标
     **/
    void updateTestDebugCoordinate(Vec2 cursor);
    
private:
    
    //初始化进来的数据
    int m_w ,m_h;
    float m_x ,m_y;
    string m_ImageName;
    bool m_isDebug;
    
    //判断双击的时间
    unsigned long clickTime1;
    
    //记录点击的次数
    int clickCount;
    
    //记录双击是否点中同一个点（严谨的双击）
    Vec2 clickDownPoint1,clickDownPoint2;
    
    //鼠标当前的坐标
    Vec2 cursorVec2;
    
    //记录节点数量
    int coordinateCount;
    
    typedef void (Ref::*Handler)(Ref*, cocos2d::extension::Control::EventType);
    
    ControlButton* createButton(Scale9Sprite *sprite,Handler action);
private:
    
    Widget *mWidget;
    
private:
    
    virtual void onMouseDown(Event *event);
    
    virtual void onMouseMove(Event *event);
    
    virtual void onMouseScroll(Event *event);
    
    virtual void onMouseUp(Event *event);
    
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
};
#endif /* defined(__UI__UIWorkScene__) */
