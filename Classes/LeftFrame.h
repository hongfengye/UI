//
//  LeftFrame.h
//  UICoordinate
//
//  Created by dzp on 14-7-8.
//
//

#ifndef __UICoordinate__LeftFrame__
#define __UICoordinate__LeftFrame__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class LeftFrame : public ScrollView{
public:
    static LeftFrame *createScene(const char* pathName,Size frameSize);
    bool init(const char* pathName,Size frameSize);
    
public:
    void setFilePath(const char* path);
    vector<string> getFileNameList();
private:
    const char * filePath;
    Sprite *layer;
    
private:
    
    void updatePath(const char* path);
    Sprite* getItemAtIndex(string fileName);
    vector<string> fileList;
    
    
};

#endif /* defined(__UICoordinate__LeftFrame__) */
