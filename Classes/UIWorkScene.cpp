//
//  UIWorkScene.cpp
//  UI
//
//  Created by dzp on 14-7-16.
//
//

#include "UIWorkScene.h"
#include "HeaderFile.h"
#include "MainScene.h"
USING_NS_CC;

UIWorkScene* UIWorkScene::createLayer(bool isDebug,string imageName ,float x,float y,int w,int h)
{
    UIWorkScene *ui = new UIWorkScene();
    if(ui){
        ui->initWith(isDebug,imageName, x, y, w, h);
        ui->autorelease();
        return ui;
    }else{
        return NULL;
    }
}

void UIWorkScene::initWith(bool isDebug,string imageName,float x,float y,int w,int h)
{
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;
    m_ImageName = imageName;
    m_isDebug = isDebug;
    
    mWidget = Widget::getInstance();
    clickCount = 0;
    clickTime1 = 0.0;
    coordinateCount = 0;
    
    auto dirctor = Director::getInstance();
    auto gl = dirctor->getOpenGLView();
    dirctor->setOpenGLView(gl);
    gl->setDesignResolutionSize(w, h, ResolutionPolicy::NO_BORDER);
    
    //开启鼠标监听
    auto listenerMouse = EventListenerMouse::create();
    listenerMouse->onMouseDown = CC_CALLBACK_1(UIWorkScene::onMouseDown, this);
    listenerMouse->onMouseMove = CC_CALLBACK_1(UIWorkScene::onMouseMove, this);
    listenerMouse->onMouseScroll = CC_CALLBACK_1(UIWorkScene::onMouseScroll, this);
    listenerMouse->onMouseUp = CC_CALLBACK_1(UIWorkScene::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);
    
    //开启键盘监听
    auto listenerKeyBoard = EventListenerKeyboard::create();
    listenerKeyBoard->onKeyPressed = CC_CALLBACK_2(UIWorkScene::onKeyPressed, this);
    listenerKeyBoard->onKeyReleased = CC_CALLBACK_2(UIWorkScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);
    
    //开启触摸监听
    auto listenerTouch = EventListenerTouchOneByOne::create();
    listenerTouch->onTouchBegan = CC_CALLBACK_2(UIWorkScene::onTouchBegan, this);
    listenerTouch->onTouchMoved = CC_CALLBACK_2(UIWorkScene::onTouchMoved, this);
    listenerTouch->onTouchEnded = CC_CALLBACK_2(UIWorkScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);
    
    auto mainSprite = Sprite::create(imageName);
    mainSprite->setPosition(Vec2(w*0.5, h*0.5));
    mainSprite->setTag(UIWORK_BG_TAG);
    this->addChild(mainSprite);
    
    CCLOG("w = %f, h = %f",mainSprite->getContentSize().width,mainSprite->getContentSize().height);
    
    if(isDebug){
        auto testDebug = Sprite::create("zuobiao.png");
        testDebug->setTag(UIWORK_TESTDEBUG_TAG);
        this->addChild(testDebug);

        auto label = Label::createWithSystemFont("( 000 , 000 )", "Arial", 20);
        label->setPosition(Vec2(label->getContentSize().width/2 + testDebug->getContentSize().width,
                                -label->getContentSize().height/2));
        label->setTag(UIWORK_TESTDEBUG_LABEL_TAG);
        testDebug->addChild(label);
    }
    
}

Vec2 UIWorkScene::converLationinView(float cursorX, float cursorY)
{
    return Vec2( cursorX - m_x*m_w  , cursorY - m_y*m_h);
}

Vec2 UIWorkScene::converOpenglRate(cocos2d::Vec2 cursor)
{
    return Vec2(cursor.x*m_w/960,cursor.y*m_h/640);
}

Sprite* UIWorkScene::addCoordinate(cocos2d::Vec2 v)
{
    ++coordinateCount;
    
    auto Coordinate = Sprite::create("zuobiao.png");
    Coordinate->setPosition(v);
    Coordinate->setTag(UIWORK_ZUOBIAO_TAG+coordinateCount);
    this->addChild(Coordinate);
    
    Vec2 converV = converLationinView(v.x,v.y);
    
    char buff[255];
    sprintf(buff, "( %d , %d )" , (int)converV.x,(int)converV.y);
    auto label = Label::createWithSystemFont(buff, "Arial", 20);
    label->setPosition(Vec2(label->getContentSize().width/2 + Coordinate->getContentSize().width,
                            -label->getContentSize().height/2));
    label->setTag(UIWORK_ZUOBIAO_LABEL_TAG);
    Coordinate->addChild(label);
    
    return Coordinate;
}

void UIWorkScene::updateTestDebugCoordinate(Vec2 cursor)
{
    auto testDebug = static_cast<Sprite*>(this->getChildByTag(UIWORK_TESTDEBUG_TAG));
    auto label = static_cast<Label*>( testDebug->getChildByTag(UIWORK_TESTDEBUG_LABEL_TAG));
    
    testDebug->setPosition(cursor);
    char buff[255];
    Vec2 v = converLationinView(testDebug->getPositionX(), testDebug->getPositionY());
    sprintf(buff, "( %d , %d )" , (int)v.x,(int)v.y);
    label->setString(buff);
}

void UIWorkScene::updateCoordinate(cocos2d::Sprite *sprite)
{
    auto label = static_cast<Label*>( sprite->getChildByTag(UIWORK_ZUOBIAO_LABEL_TAG));
    char buff[255];
    Vec2 v = converLationinView(sprite->getPositionX(), sprite->getPositionY());
    sprintf(buff, "( %d , %d )" , (int)v.x,(int)v.y);
    label->setString(buff);
}


//,Control::EventType controlEvent
void UIWorkScene::saveCallBack(cocos2d::Ref *sender)
{
    RenderTexture *render;
    this->runAction(Sequence::create(CallFunc::create([&]{
        this->removeChildByTag(UIWORK_PANEL_TAG);
    }),
                                     DelayTime::create(0.5),
                                     CallFunc::create([&]{
        auto scene = Director::getInstance()->getRunningScene();
        render = RenderTexture::create(m_w, m_h, Texture2D::PixelFormat::RGBA8888);
        render->begin();
        scene->visit();
        render->end();
    }),
                                     CallFunc::create([&]{
        char buff[255];
        sprintf(buff, "NEW_%s",m_ImageName.c_str());
        render->saveToFile(buff, Image::Format::PNG);
        CCLOG("save successful");
    }),
                                     NULL));
    
}

void UIWorkScene::exitCallBack(cocos2d::Ref *sender)
{
    auto dirctor = Director::getInstance();
    auto gl = dirctor->getOpenGLView();
    dirctor->setOpenGLView(gl);
    
    
    Director::getInstance()->replaceScene(MainScene::createScene());
}

void UIWorkScene::cancelCallBack(cocos2d::Ref *sender)
{
    this->removeChildByTag(UIWORK_PANEL_TAG);
}

Sprite* UIWorkScene::createPanel(UIWorkScene::PanelType panelType)
{
    auto panel = Sprite::create();
    panel->setContentSize(Size(200, 150));
    panel->setPosition(Vec2(m_w/2, m_h/2));
    panel->setTag(UIWORK_PANEL_TAG);
    auto layerColor = LayerColor::create(Color4B(255, 255, 255, 255), panel->getContentSize().width, panel->getContentSize().height);
    panel->addChild(layerColor);
    Label *title,*msg;
    if(panelType == PanelType::exit){
        title = Label::createWithSystemFont("是否退出？", "Arial", 22);
        title->setColor(Color3B::BLACK);
        title->setPosition(Vec2(panel->getContentSize().width/2,
                                panel->getContentSize().height-title->getContentSize().height/2-2));
        msg = Label::createWithSystemFont("退出后，操作不作保存", "Arial", 20);
        msg->setColor(Color3B::BLACK);
        msg->setPosition(Vec2(panel->getContentSize().width/2, panel->getContentSize().height/2));
    }else if (panelType == PanelType::save){
        title = Label::createWithSystemFont("是否保存？", "Arial", 22);
        title->setColor(Color3B::BLACK);
        title->setPosition(Vec2(panel->getContentSize().width/2,
                                panel->getContentSize().height-title->getContentSize().height/2-2));
        msg = Label::createWithSystemFont("保存所有操作", "Arial", 20);
        msg->setColor(Color3B::BLACK);
        msg->setPosition(Vec2(panel->getContentSize().width/2, panel->getContentSize().height/2));
    }
    panel->addChild(title);
    panel->addChild(msg);
    
    MenuItemImage *itemExit,*itemSave,*itemCancel;
    itemCancel = MenuItemImage::create("cancel.png", "cancel.png", CC_CALLBACK_1(UIWorkScene::cancelCallBack, this));
    itemCancel->setPosition(Vec2(panel->getContentSize().width/4, itemCancel->getContentSize().height/2+5));
    
    if(panelType == PanelType::exit){
        itemExit = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(UIWorkScene::exitCallBack, this));
        itemExit->setPosition(Vec2(3*panel->getContentSize().width/4, itemExit->getContentSize().height/2+5));
        auto menu = Menu::create(itemExit,itemCancel, NULL);
        menu->setPosition(Vec2::ZERO);
        panel->addChild(menu);
    }
    if(panelType == PanelType::save){
        itemSave = MenuItemImage::create("save.png", "save.png", CC_CALLBACK_1(UIWorkScene::saveCallBack, this));
        itemSave->setPosition(Vec2(3*panel->getContentSize().width/4, itemSave->getContentSize().height/2+5));
        auto menu = Menu::create(itemSave,itemCancel, NULL);
        menu->setPosition(Vec2::ZERO);
        panel->addChild(menu);
    }
    
    
    return panel;
    
}



void UIWorkScene::onMouseDown(cocos2d::Event *event)
{
    EventMouse *e = (EventMouse*)event;
    Vec2 v = Vec2(e->getCursorX(), e->getCursorY());
    
    //判断是否关闭panel
    if(static_cast<Sprite*>(this->getChildByTag(UIWORK_PANEL_TAG))!=NULL){
        auto panel = static_cast<Sprite*>(this->getChildByTag(UIWORK_PANEL_TAG));
        auto nodePos = panel->convertToNodeSpace(converOpenglRate(v));
        auto nodeRect = Rect(0, 0, panel->getContentSize().width, panel->getContentSize().height);
        if(!nodeRect.containsPoint(nodePos)){
            this->removeChildByTag(UIWORK_PANEL_TAG);
        }
        return;
    }
    
    //增加坐标数据显示
    addCoordinate(converOpenglRate(v));
    
    /*判断双击的逻辑*/
    if( (mWidget->getCurrentTimemillisecond() - clickTime1)/1000 >0.7 ){
        clickCount = 0;
    }
    if(clickCount == 0){
        clickTime1 = mWidget->getCurrentTimemillisecond();
        clickDownPoint1 = Vec2( e->getCursorX(), e->getCursorY() );
    }else if(clickCount == 1){
        clickDownPoint2 = Vec2( e->getCursorX(), e->getCursorY() );
    }
    ++clickCount;
    
    
}

void UIWorkScene::onMouseMove(cocos2d::Event *event)
{
    EventMouse* e = (EventMouse*)event;
    cursorVec2 = converOpenglRate( Vec2(e->getCursorX(), e->getCursorY()));
    if(m_isDebug){
        updateTestDebugCoordinate(cursorVec2);
        
    }
    log("null x = %f , y = %f ", e->getCursorX(),e->getCursorY());
    log("opengl x = %f , y = %f ", converOpenglRate( Vec2(e->getCursorX(), e->getCursorY())).x,
        converOpenglRate( Vec2(e->getCursorX(), e->getCursorY())).y);
    log("Laction x = %f , y = %f ", converLationinView(e->getCursorX(),e->getCursorY()).x,
        converLationinView(e->getCursorX(),e->getCursorY()).y);
    
    
}

void UIWorkScene::onMouseScroll(cocos2d::Event *event)
{
}

void UIWorkScene::onMouseUp(cocos2d::Event *event)
{
    EventMouse* e = (EventMouse*)event;
    Vec2 clickUpPoint = Vec2(e->getCursorX(), e->getCursorY());
    if(clickCount == 2){
        clickCount = 0;
        Vec2 clickUpPoint = Vec2( ((EventMouse*)event)->getCursorX(),((EventMouse*)event)->getCursorY() );
        bool isClickSamePoint1 = mWidget->isEqualVec1AndVec2(clickUpPoint, clickDownPoint1); //防止移动
        bool isClickSamePoint2 = mWidget->isEqualVec1AndVec2(clickUpPoint, clickDownPoint2); //防止移动
        bool isClickSamePoint3 = mWidget->isEqualVec1AndVec2(clickDownPoint1, clickDownPoint2); //防止拖动
        
        if( isClickSamePoint1 && isClickSamePoint2 && isClickSamePoint3  ){
            //双击操作，切换背景图
            
            CCLOG("双击了");
        }else{
            CCLOG("双击失败了");
            return;
        }
    }
}

void UIWorkScene::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    auto s = static_cast<Sprite*>(this->getChildByTag(UIWORK_ZUOBIAO_TAG+coordinateCount));
    if(keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW){
        s->setPosition(s->getPosition() + Vec2(0, 1));
        updateCoordinate(s);
    }else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW){
        s->setPosition(s->getPosition() + Vec2(0, -1));
        updateCoordinate(s);
    }else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW){
        s->setPosition(s->getPosition() + Vec2(-1, 0));
        updateCoordinate(s);
    }else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
        s->setPosition(s->getPosition() + Vec2(1, 0));
        updateCoordinate(s);
    }else if (keyCode == EventKeyboard::KeyCode::KEY_DELETE){
        //删除坐标
        int i;
        for ( i = 1; i <= coordinateCount; ++i) {
            auto s = static_cast<Sprite*>(this->getChildByTag(UIWORK_ZUOBIAO_TAG+i));
            auto nodePos = s->convertToNodeSpace(converOpenglRate( cursorVec2));
            auto nodeRect = Rect(0, 0, s->getContentSize().width, s->getContentSize().height);
            if(nodeRect.containsPoint(nodePos)){
                this->removeChild(s);
                --coordinateCount;
                break;
            }
        }

        //重构坐标的标记
        for (int j = i; j<=coordinateCount; ++j) {
            auto s = static_cast<Sprite*>(this->getChildByTag(UIWORK_ZUOBIAO_TAG+j+1));
            s->setTag(UIWORK_ZUOBIAO_TAG+j);
            
        }
        
    }else if (keyCode == EventKeyboard::KeyCode::KEY_S){
        if(static_cast<Sprite*>(this->getChildByTag(UIWORK_PANEL_TAG))==NULL){
            this->addChild(createPanel(PanelType::save));
        }
    }
}

void UIWorkScene::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    //Esc
    if((int)keyCode == 6){
        if(static_cast<Sprite*>(this->getChildByTag(UIWORK_PANEL_TAG))==NULL){
            this->addChild(createPanel(PanelType::exit));
        }else{
            this->removeChildByTag(UIWORK_PANEL_TAG);
        }
    }
    
    
}

bool UIWorkScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}

void UIWorkScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void UIWorkScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}



//ControlButton* UIWorkScene::createButton(cocos2d::extension::Scale9Sprite *sprite, Handler action)
//{
//    auto button = ControlButton::create(sprite);
//    button->setPreferredSize(sprite->getContentSize());
//    button->addTargetWithActionForControlEvents(this, action, Control::EventType::TOUCH_UP_INSIDE);
//    return button;
//}




