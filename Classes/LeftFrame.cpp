//
//  LeftFrame.cpp
//  UICoordinate
//
//  Created by dzp on 14-7-8.
//
//

#include "LeftFrame.h"
#include "HeaderFile.h"
#include "FindFileInfo.h"
using namespace std;

LeftFrame* LeftFrame::createScene(const char *pathName, Size frameSize)
{
    LeftFrame *left = new LeftFrame();
    if(left && left->init(pathName,frameSize)){
        left->autorelease();
        return left;
    }else{
        return NULL;
    }
}

bool LeftFrame::init(const char *pathName,Size frameSize)
{
    this->setViewSize(frameSize);
    this->setContentSize(Size(frameSize.width*3,frameSize.height));
    this->setDirection(ScrollView::Direction::HORIZONTAL);
    this->setBounceable(false);
    this->setTouchEnabled(false);
    
    layer = Sprite::create();
    layer->setContentSize(Size(frameSize.width*3,frameSize.height));
    this->setContainer(layer);
    
    filePath = pathName;
    updatePath(filePath);
    
    
    return true;
}

void LeftFrame::updatePath(const char* path)
{
    fileList = FindFileInfo::getInstance()->getFileList(path);
    if((int)fileList.size() == 0){
        layer->removeAllChildren();
        auto tipLabel = Label::createWithSystemFont("Nothing", "Arial", 25);
        tipLabel->setPosition(Vec2(this->getViewSize().width/2, this->getViewSize().height/2));
        layer->addChild(tipLabel);
    }else{
        layer->removeAllChildren();
        for (int i = 0 ; i < (int)fileList.size(); ++i) {
            auto child = getItemAtIndex(fileList.at(i));
            layer->addChild(child);
            Vec2 childPos = Vec2(child->getContentSize().width/2,
                                 layer->getContentSize().height - (2*i+1)*(child->getContentSize().height/2));
            child->setPosition(childPos);
            child->setTag(Left_sprite_tag+i+1);
        }
    }
}

Sprite* LeftFrame::getItemAtIndex(string fileName)
{
    //创建一个item
    auto mainItemOnce = Sprite::create();
    mainItemOnce->setContentSize(Size(layer->getContentSize().width,Left_item_height));
    
    //创建item里面的一个子项 — —显示图片
    auto picOnce = Sprite::create();
    picOnce->setContentSize(Size(Left_pic_width,Left_pic_height));
    picOnce->setPosition(Vec2(picOnce->getContentSize().width/2+10, mainItemOnce->getContentSize().height/2));
    
    //创建item里面的一个子项 — —显示文件名
    auto labOnce = Label::createWithSystemFont(fileName, "Arial", 18);
    labOnce->setPosition(Vec2(picOnce->getPositionX() + picOnce->getContentSize().width/2+5,
                              mainItemOnce->getContentSize().height/2));
    labOnce->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

    //按比例缩放显示的图片，总让它显示在中间
    auto pic = Sprite::create(fileName);
    int p_w = pic->getContentSize().width;
    int p_h = pic->getContentSize().height;
    int max_d = p_w>p_h?p_w:p_h;
    float scale_rate = picOnce->getContentSize().width / max_d;
    pic->setScale(scale_rate,scale_rate);
    pic->setPosition(picOnce->getContentSize().width/2,picOnce->getContentSize().height/2);
    picOnce->addChild(pic);
    
    mainItemOnce->addChild(picOnce);
    mainItemOnce->addChild(labOnce);
    return mainItemOnce;
}

void LeftFrame::setFilePath(const char *path)
{
    updatePath(path);
}

vector<string> LeftFrame::getFileNameList()
{
    return fileList;
}
