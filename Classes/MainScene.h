//
//  MainScene.h
//  UICoordinate
//
//  Created by dzp on 14-7-7.
//
//

#ifndef __UICoordinate__MainScene__
#define __UICoordinate__MainScene__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "LeftFrame.h"
#include "Widget.h"
#include "UserDataManager.h"
#include "HeaderFile.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;



class MainScene : public Layer, public EditBoxDelegate , public ScrollViewDelegate
{
public:
enum InputKinds{
    X=Middle_spriteX_tag,
    Y=Middle_spriteY_tag,
    W=Middle_spriteW_tag,
    H=Middle_spriteH_tag
};
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    MainScene();
    
    ~MainScene();
    
private:
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated);
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox *editBox);
    
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox *editBox);
    
    virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);
    
    virtual void editBoxTextChanged(cocos2d::extension::EditBox *editBox, const std::string &text);
    
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView *view);
    
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView *view);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    virtual void onMouseDown(Event *event);
    
    virtual void onMouseMove(Event *event);
    
    virtual void onMouseScroll(Event *event);
    
    virtual void onMouseUp(Event *event);
    
private:

    void addTopLayer();
    
    void addLeftLayer();
    
    void addMiddleLayer();
    
    void surePathCallBack();
    
    Sprite *getMiddleInputSprite(InputKinds inputK);
    
private:
    char *pathName; //路径
    int itemCount; //搜索到的图片数量
    int clickIndex;//选中的索引
    Vec2 beganPoint;//开始点击的位置

    
    unsigned long clickTime1; //判断双击的时间
    int clickCount;  //记录点击的次数
    Vec2 clickDownPoint1,clickDownPoint2; //记录双击是否点中同一个点（严谨的双击）
    
    
    vector<string> FileNameVector; //获取所有文件名的容器
    bool isDoubleClick; //判断是否选中一张图片
    
    bool isDebug; //是否开启鼠标监控
    
    float scrollMaxPos; //滑动的下限
    float scrollDistance; //滑动的距离
    
private:
    LeftFrame *leftItem;
    Widget *mWidget;
    UserDataManager *mUserDataManager;

};
#endif /* defined(__UICoordinate__MainScene__) */
