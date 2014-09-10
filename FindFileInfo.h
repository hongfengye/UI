//
//  FindFileInfo.h
//  TestThreeApp
//
//  Created by dzp on 14-7-6.
//
//

#ifndef __TestThreeApp__FindFileInfo__
#define __TestThreeApp__FindFileInfo__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class FindFileInfo : public Ref{
public:
    /*此路径path不能带有中文名字*/
    vector<const char*> getFileList(const char* path);
    static FindFileInfo *getInstance();
    
private:
    
    bool isJpgOrPng(const char* fileName);
};




#endif /* defined(__TestThreeApp__FindFileInfo__) */


