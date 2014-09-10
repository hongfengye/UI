//
//  FindFileInfo.h
//  UI
//
//  Created by dzp on 14-7-21.
//
//

#ifndef __UI__FindFileInfo__
#define __UI__FindFileInfo__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class FindFileInfo : public Ref{
public:
    /*此路径path不能带有中文名字*/
    vector<string> getFileList(const char* path);
    static FindFileInfo *getInstance();
    
private:
    vector<string> p; //添加子路径的中间变量
    vector<string> fileNameList_C; //储存文件名
    void readFileList(char *basePath);
    bool isJpgOrPng(const char* fileName);
};

#endif /* defined(__UI__FindFileInfo__) */
