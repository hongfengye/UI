//
//  UserDataManager.h
//  UICoordinate
//
//  Created by dzp on 14-7-15.
//
//

#ifndef __UICoordinate__UserDataManager__
#define __UICoordinate__UserDataManager__

#include <iostream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class UserDataManager : public Ref{
public:
    static UserDataManager* getInstance();
    

public:
    void setUserPaths(string path);
    string getUserPaths();
    
    void setOriginX(float x);
    float getOriginX();
    
    void setOriginY(float y);
    float getOriginY();
    
    void setOpenGLWidth(int w);
    int getOpenGLWidth();
    
    void setOpenGLHeight(int h);
    int getOpenGLHeight();
    
    void setIsDebug(bool isDebug);
    bool getIsDebug();
    
    
private:
    
};
#endif /* defined(__UICoordinate__UserDataManager__) */
