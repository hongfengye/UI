//
//  MainScene.cpp
//  UICoordinate
//
//  Created by dzp on 14-7-7.
//
//

#include "MainScene.h"
#include "UIWorkScene.h"


USING_NS_CC;
USING_NS_CC_EXT;



MainScene::MainScene()
{
    mWidget = Widget::getInstance();
    mUserDataManager = UserDataManager::getInstance();
    isDoubleClick = false;
    isDebug = false;
    clickCount = 0;
    clickTime1 = 0.0;
    scrollMaxPos = 0;
    scrollDistance =0;
    
    auto listenerTouch = EventListenerTouchOneByOne::create();
    listenerTouch->setSwallowTouches(true);
    listenerTouch->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    listenerTouch->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
    listenerTouch->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);
    
    auto listenerMouse = EventListenerMouse::create();
    listenerMouse->onMouseDown = CC_CALLBACK_1(MainScene::onMouseDown, this);
    listenerMouse->onMouseMove = CC_CALLBACK_1(MainScene::onMouseMove, this);
    listenerMouse->onMouseScroll = CC_CALLBACK_1(MainScene::onMouseScroll, this);
    listenerMouse->onMouseUp = CC_CALLBACK_1(MainScene::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);
    
}

MainScene::~MainScene()
{
    
}

void MainScene::onEnter()
{
    Layer::onEnter();
}

void MainScene::onExit()
{
    Layer::onExit();
}

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MainScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    addTopLayer();
    
    addLeftLayer();
    
    addMiddleLayer();
    
    //响应确定路径事件
    surePathCallBack();
    return true;
    
}

void MainScene::addTopLayer()
{
    /*添加顶部信息*/
    auto layerTop = Sprite::create();
    layerTop->setContentSize(Size(WinSize.width, Top_parent_Height));
    layerTop->setTag(Top_parent_Tag);
    layerTop->setPosition(Vec2(0, WinSize.height));
    layerTop->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    this->addChild(layerTop);
    
    auto editPath = EditBox::create(Size(WinSize.width/2, Top_parent_Height*3/4), Scale9Sprite::create("inputBG.png"));
    editPath->setPosition(Vec2(WinSize.width/2, Top_parent_Height/2));
    editPath->setTag(Top_inputBox_tag);
    editPath->setDelegate(this);
    editPath->setInputMode(EditBox::InputMode::ANY);
    editPath->setText(mUserDataManager->getUserPaths().c_str());
    layerTop->addChild(editPath);
    
    auto labelPath = Label::createWithSystemFont("路径", "Arial", 22);
    labelPath->setPosition(Vec2((editPath->getPositionX()-editPath->getContentSize().width/2)/2, Top_parent_Height/2));
    layerTop->addChild(labelPath);
    
    auto itemSure = MenuItemLabel::create(Label::createWithSystemFont("确定", "Arial", 22), CC_CALLBACK_1(MainScene::menuCallback,this));
    itemSure->setTag(Top_sure_tag);
    itemSure->setPosition(Vec2((mWidget->getConverNodeVec2ByX(editPath)+WinSize.width)/2, Top_parent_Height/2));
    auto menu = Menu::create(itemSure, NULL);
    menu->setPosition(Vec2::ZERO);
    layerTop->addChild(menu);
    
}

void MainScene::addLeftLayer()
{
    /*添加左部栏*/
    auto layerLeft = Sprite::create();
    layerLeft->setContentSize(Size(Left_parent_Width, Left_parent_Height));
    leftItem = LeftFrame::createScene("", Size(Left_parent_Width, Left_parent_Height));
    leftItem->setDelegate(this);
    leftItem->setTag(Left_scroll_tag);
    layerLeft->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    layerLeft->setPosition(Vec2(0, Left_parent_Height-1));
    layerLeft->addChild(leftItem);
    layerLeft->setTag(Left_parent_Tag);
    auto layerLeftColor = LayerColor::create(Color4B(128, 128, 128, 255),layerLeft->getContentSize().width,layerLeft->getContentSize().height);
    layerLeft->addChild(layerLeftColor,-1);
    this->addChild(layerLeft);
    
}

void MainScene::addMiddleLayer()
{
    /*添加中部栏*/
    auto layerMiddle = Sprite::create();
    layerMiddle->setContentSize(Size(Middle_parent_width,Middle_parent_height));
    layerMiddle->setTag(Middle_parent_Tag);
    layerMiddle->setPosition(Vec2(Left_parent_Width + Top_line_height,0));
    layerMiddle->setAnchorPoint(Vec2::ZERO);
    this->addChild(layerMiddle);
    
    auto labelTip2 = Label::createWithSystemFont("自定义原点", "Arial", 19);
    auto labelTip1 = Label::createWithSystemFont("你选择了", "Arial", 19);
    labelTip1->setPosition(Vec2(labelTip2->getContentSize().width/2, Middle_parent_height-Middle_space_height));
    layerMiddle->addChild(labelTip1);
    auto showChooseSprite = Sprite::create();
    showChooseSprite->setPosition(Vec2((Middle_parent_width-labelTip1->getContentSize().width)/2, labelTip1->getPositionY()));
    showChooseSprite->setTag(Middle_choose_bg_tag);
    layerMiddle->addChild(showChooseSprite);
    
    labelTip2->setPosition(Vec2(labelTip2->getContentSize().width/2,
                                layerMiddle->getContentSize().height-2*Middle_space_height));
    layerMiddle->addChild(labelTip2);
    
    //添加输入框X
    auto spriteX = getMiddleInputSprite(InputKinds::X);
    layerMiddle->addChild(spriteX);
    
    auto labelTip3 = Label::createWithSystemFont("选择分辨率", "Arial", 19);
    labelTip3->setPosition(Vec2(labelTip3->getContentSize().width/2,
                                layerMiddle->getContentSize().height-3*Middle_space_height));
    layerMiddle->addChild(labelTip3);
    
    //添加输入框Y
    auto spriteY = getMiddleInputSprite(InputKinds::Y);
    layerMiddle->addChild(spriteY);
    
    //添加输入框W
    auto spriteW = getMiddleInputSprite(InputKinds::W);
    layerMiddle->addChild(spriteW);
    
    //添加输入框H
    auto spriteH = getMiddleInputSprite(InputKinds::H);
    layerMiddle->addChild(spriteH);
    
    //添加鼠标滚动debug菜单
    string state;
    if(mUserDataManager->getIsDebug()){
        state = "On";
    }else{
        state = "Debug";
    }
    auto itemDebug = MenuItemLabel::create(Label::createWithSystemFont(state, "Arial", 20), CC_CALLBACK_1(MainScene::menuCallback, this));
    itemDebug->setTag(Middle_debug_tag);
    itemDebug->setPosition(itemDebug->getContentSize().width/2,itemDebug->getContentSize().height/2);
    
    //添加开始菜单
    auto itemStart = MenuItemLabel::create(Label::createWithSystemFont("  开  始  ", "Arial", 22), CC_CALLBACK_1(MainScene::menuCallback,this));
    itemStart->setTag(Middle_start_tag);
    itemStart->setPosition(Vec2(layerMiddle->getContentSize().width/2, 150));
    auto menuStart = Menu::create(itemStart,itemDebug, NULL);
    menuStart->setPosition(Vec2::ZERO);
    layerMiddle->addChild(menuStart);
    
    
}

void MainScene::surePathCallBack()
{

    auto parentLayer = this->getChildByTag(Top_parent_Tag);
    auto inputBox = (EditBox*)parentLayer->getChildByTag(Top_inputBox_tag);
    const char* thisPath = inputBox->getText();
    leftItem->setFilePath(thisPath);
    //储存上一次的路径
    UserDataManager::getInstance()->setUserPaths(thisPath);
    //获取文件名的个数
    itemCount = (int)leftItem->getFileNameList().size();
    //储存所有文件名
    for (int i = 0; i< itemCount; ++i) {
        FileNameVector.push_back(leftItem->getFileNameList().at(i));
    }
    
}

Sprite* MainScene::getMiddleInputSprite(MainScene::InputKinds inputK)
{
    Sprite* sprite = Sprite::create();
    sprite->setContentSize(Middle_inputBox_size);
    sprite->setTag(inputK);
    
    string text;
    int tag;
    char buff[255];
    
    if(inputK == InputKinds::X){
        text = "X : ";
        tag = Middle_inputX_tag;
        sprintf(buff, "%.1f",mUserDataManager->getOriginX());
        sprite->setPosition(Vec2(Middle_parent_width/2-100, Middle_parent_height- 2*Middle_space_height));
    }else if (inputK == InputKinds::Y){
        text = "Y : ";
        tag = Middle_inputY_tag;
        sprintf(buff, "%.1f",mUserDataManager->getOriginY());
        sprite->setPosition(Vec2(Middle_parent_width/2+150, Middle_parent_height- 2*Middle_space_height));
    }else if (inputK == InputKinds::W){
        text = "W : ";
        tag = Middle_inputW_tag;
        sprintf(buff, "%d",mUserDataManager->getOpenGLWidth());
        sprite->setPosition(Vec2(Middle_parent_width/2-100, Middle_parent_height- 3*Middle_space_height));
    }else if (inputK == InputKinds::H){
        text = "H : ";
        tag = Middle_inputH_tag;
        sprintf(buff, "%d",mUserDataManager->getOpenGLHeight());
        sprite->setPosition(Vec2(Middle_parent_width/2+150, Middle_parent_height- 3*Middle_space_height));
    }

    auto label = Label::createWithSystemFont(text.c_str(), "Arial", 22);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    label->setPosition(Vec2(0, sprite->getContentSize().height/2));
    sprite->addChild(label);
    
    auto edit = EditBox::create(Size(Middle_inputBox_size.width-label->getContentSize().width,
                                     sprite->getContentSize().height), Scale9Sprite::create("inputBG.png"));
    edit->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    edit->setPosition(Vec2(sprite->getContentSize().width, sprite->getContentSize().height/2));
    edit->setDelegate(this);
    edit->setInputMode(EditBox::InputMode::NUMERIC);
    edit->setText((const char*)buff);
    edit->setTag(tag);
    sprite->addChild(edit);
    
    return sprite;
}


void MainScene::menuCallback(cocos2d::Ref *pSender)
{
    auto label = static_cast<MenuItemLabel*>(pSender);
    int tag = label->getTag();
    if (tag == Top_sure_tag){  //确定路径
        surePathCallBack();
    }else if (tag == Middle_start_tag){  //开始
        if(!isDoubleClick){
            MessageBox("请选择一张张图", "温馨提示");
            return;
        }
        auto layerMiddle = static_cast<Sprite*>(this->getChildByTag(Middle_parent_Tag));
        auto editX = static_cast<EditBox*>(layerMiddle->getChildByTag(InputKinds::X)->getChildByTag(Middle_inputX_tag));
        auto editY = static_cast<EditBox*>(layerMiddle->getChildByTag(InputKinds::Y)->getChildByTag(Middle_inputY_tag));
        auto editW = static_cast<EditBox*>(layerMiddle->getChildByTag(InputKinds::W)->getChildByTag(Middle_inputW_tag));
        auto editH = static_cast<EditBox*>(layerMiddle->getChildByTag(InputKinds::H)->getChildByTag(Middle_inputH_tag));
        float x = atof(editX->getText());
        if( !(x >=0.0 && x <=1.0) ){
            MessageBox("X请输入0-1的数字", "温馨提示");
            return;
        }
        float y = atof(editY->getText());
        if( !(y >=0.0 && y <=1.0) ){
            MessageBox("Y请输入0-1的数字", "温馨提示");
            return;
        }
        int w = atoi(editW->getText());
        if( !(w >=480 && w <=1400) ){
            MessageBox("W请输入480-1400的数字", "温馨提示");
            return;
        }
        int h = atoi(editH->getText());
        if( !(h >=480 && h <=1000) ){
            MessageBox("H请输入480-1000的数字", "温馨提示");
            return;
        }
        
        //保存数据
        mUserDataManager->setOriginX(x);
        mUserDataManager->setOriginY(y);
        mUserDataManager->setOpenGLWidth(w);
        mUserDataManager->setOpenGLHeight(h);
        mUserDataManager->setIsDebug(isDebug);
        
        auto s = Scene::create();
        s->addChild(UIWorkScene::createLayer(isDebug,FileNameVector.at(clickIndex-1), x, y, w, h));
        Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(.5, s));
    }else if (tag == Middle_debug_tag){
        auto text = static_cast<Label*>( label->getLabel());
        if(mUserDataManager->getIsDebug()){
            text->setString("Debug");
            isDebug = false;
        }else{
            text->setString("On");
            isDebug = true;
        }
        mUserDataManager->setIsDebug(isDebug);
    }
}


void MainScene::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated)
{
    ::glLineWidth(Top_line_height);
    ::glColorMask(255, 255, 255, 255);
    DrawPrimitives::drawLine(Vec2(0, WinSize.height - Top_parent_Height - Top_line_height),
                             Vec2(WinSize.width, WinSize.height - Top_parent_Height - Top_line_height));
    DrawPrimitives::drawLine(Vec2(Left_parent_Width + Top_line_height, WinSize.height - Top_parent_Height - Top_line_height),
                             Vec2(Left_parent_Width + Top_line_height, 0));
    
}

void MainScene::editBoxEditingDidBegin(cocos2d::extension::EditBox *editBox)
{}

void MainScene::editBoxEditingDidEnd(cocos2d::extension::EditBox *editBox)
{
}

void MainScene::editBoxReturn(cocos2d::extension::EditBox *editBox)
{
}

void MainScene::editBoxTextChanged(cocos2d::extension::EditBox *editBox, const std::string &text)
{}

void MainScene::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{}

void MainScene::scrollViewDidZoom(cocos2d::extension::ScrollView *view)
{}


bool MainScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    //////////////////////////
    //处理左部信息栏的精灵拖动
    beganPoint = touch->getLocation();
    for (int i = 1; i <=itemCount ; ++i) {

        auto leftParent = static_cast<Sprite*>( this->getChildByTag(Left_parent_Tag));
        auto leftScroll = static_cast<ScrollView*>(leftParent->getChildByTag(Left_scroll_tag));
        auto scrollContain = static_cast<Sprite*>(leftScroll->getContainer());
        Sprite *item = static_cast<Sprite*>( scrollContain->getChildByTag(Left_sprite_tag+i));
        
        Vec2 nodePos = item->convertToNodeSpace(beganPoint);
        Rect nodeRect = Rect(0, 0, item->getContentSize().width, item->getContentSize().height);
        if(nodeRect.containsPoint(nodePos)){
            clickIndex = i;  //记录索引
            return true;
        }
    }
    
    return false;
}

void MainScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}

void MainScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void MainScene::onMouseDown(cocos2d::Event *event)
{
    /*判断双击的逻辑*/
    EventMouse* e = (EventMouse*)event;
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

void MainScene::onMouseMove(cocos2d::Event *event)
{
}

void MainScene::onMouseScroll(cocos2d::Event *event)
{
    EventMouse *e = (EventMouse*)event;
    Vec2 cursorVec2 = Vec2(e->getCursorX(), WinSize.height + e->getCursorY());
    auto layerLeft = static_cast<Sprite*>(this->getChildByTag(Left_parent_Tag));
    auto nodePos = layerLeft->convertToNodeSpace(cursorVec2);
    auto nodeRect = Rect(0, 0, layerLeft->getContentSize().width, layerLeft->getContentSize().height);
    if(nodeRect.containsPoint(nodePos)){
        float scrollY = e->getScrollY() * 6;
        if(itemCount>0){
            if(itemCount*Left_item_height < Left_parent_Height){
                return;
            }

            auto scroll = static_cast<ScrollView*>(layerLeft->getChildByTag(Left_scroll_tag));
            auto container = static_cast<Sprite*>(scroll->getContainer());
            
            auto curPos  = container->getPosition();
            auto nextPos = Vec2(curPos.x, curPos.y + scrollY);
            
            if(nextPos.y < 0.0f){
                container->setPosition(Vec2::ZERO);
                return;
            }
            
            if(nextPos.y > itemCount*Left_item_height - Left_parent_Height){
                container->setPosition( Vec2(0, itemCount*Left_item_height - Left_parent_Height));
                return;
            }

            container->setPosition(nextPos);
            
        }else{
            return;
        }
    }else{
        return;
    }
    
}

void MainScene::onMouseUp(cocos2d::Event *event)
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
            auto choose = static_cast<Sprite*>( this->getChildByTag(Middle_parent_Tag)->getChildByTag(Middle_choose_bg_tag));
            choose->setTexture(FileNameVector.at(clickIndex-1));
            int sw = choose->getContentSize().width;
            int sh = choose->getContentSize().height;
            int t = sw>sh?sw:sh;
            float rateS = Middle_choose_bg_Size.width/t;
            choose->setScale(rateS, rateS);
            isDoubleClick = true;
            CCLOG("双击了");
        }else{
            CCLOG("双击失败了");
            return;
        }
    }
}

