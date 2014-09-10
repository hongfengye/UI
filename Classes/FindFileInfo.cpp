//
//  FindFileInfo.cpp
//  UI
//
//  Created by dzp on 14-7-21.
//
//

#include "FindFileInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

FindFileInfo* FindFileInfo::getInstance()
{
    FindFileInfo *file = new FindFileInfo();
    if(file){
        return file;
    }else{
        return NULL;
    }
}

/**
 获取文件夹下的所有符合图片格式文件名
 **/
vector<string> FindFileInfo::getFileList(const char *path)
{
    /*储存符合条件的文件名*/
    vector<string> files;
    
    /*设置指定路径*/
    p.push_back(path);
    FileUtils::getInstance()->setSearchPaths(p);
    
    /*获取指定路径的所有文件名*/
    readFileList((char*)path);

    /*判断是否是.jpg或.png格式的图片*/
    for (int i = 0; i<(int)fileNameList_C.size(); ++i) {
        if(isJpgOrPng(fileNameList_C.at(i).c_str())){
            files.push_back(fileNameList_C.at(i));
        }
    }
    
    
    return files;
}


/**
 读取文件夹下的所有文件名
 **/
void FindFileInfo::readFileList(char *basePath)
{
    DIR *dir;
    struct dirent *ptr;
    char base[1000];
    
    if ((dir=opendir(basePath)) == NULL)
    {
        CCLOG("Open dir is null...");
        return;
    }
    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8)    ///file
            fileNameList_C.push_back(ptr->d_name);
        else if(ptr->d_type == 10)    ///link file
            fileNameList_C.push_back(ptr->d_name);
        else if(ptr->d_type == 4)    ///dir
        {
            memset(base,'\0',sizeof(base));
            strcpy(base,basePath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            
            //添加子路径到搜索路径
            p.push_back(base);
            FileUtils::getInstance()->setSearchPaths(p);
            
            readFileList(base);
        }
        
    }
    closedir(dir);
}

/**
 判断是是否为jpg或png图片
 **/
bool FindFileInfo::isJpgOrPng(const char *fileName)
{
    string filter[] = {".jpg",".png"};
    string strName = static_cast<string>(fileName);
    
    
    string::size_type lastPos = strName.find_last_of(".");
    if(string::npos != lastPos){
        for (int i = 0 ; i < filter->size();  ++i) {
            if(filter[i] == strName.substr(lastPos,strName.length()-lastPos)){
//                CCLOG("zhou = %s",fileName);
                return true;
            }
        }
        
    }
    return false;
}



