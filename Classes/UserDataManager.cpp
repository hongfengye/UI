//
//  UserDataManager.cpp
//  UICoordinate
//
//  Created by dzp on 14-7-15.
//
//

#include "UserDataManager.h"
#include "HeaderFile.h"
USING_NS_CC;

UserDataManager* UserDataManager::getInstance()
{
    UserDataManager *mUserDataManager = new UserDataManager();
    if(mUserDataManager){
        mUserDataManager->autorelease();
        return mUserDataManager;
    }else{
        return NULL;
    }
}

void UserDataManager::setUserPaths(string path)
{
    UserDefault::getInstance()->setStringForKey(USERPATH, path);
    UserDefault::getInstance()->flush();
}

string UserDataManager::getUserPaths()
{
    return UserDefault::getInstance()->getStringForKey(USERPATH, "");
}

void UserDataManager::setOriginX(float x)
{
    UserDefault::getInstance()->setFloatForKey(ORIGIN_X, x);
    UserDefault::getInstance()->flush();
}

float UserDataManager::getOriginX()
{
    return UserDefault::getInstance()->getFloatForKey(ORIGIN_X, 0.5);
}

void UserDataManager::setOriginY(float y)
{
    UserDefault::getInstance()->setFloatForKey(ORIGIN_Y, y);
    UserDefault::getInstance()->flush();
}

float UserDataManager::getOriginY()
{
    return UserDefault::getInstance()->getFloatForKey(ORIGIN_Y, 0.5);
}

void UserDataManager::setOpenGLWidth(int w)
{
    UserDefault::getInstance()->setIntegerForKey(OPENGL_WIDTH, w);
    UserDefault::getInstance()->flush();
}

int UserDataManager::getOpenGLWidth()
{
    return UserDefault::getInstance()->getIntegerForKey(OPENGL_WIDTH, 960);
}

void UserDataManager::setOpenGLHeight(int h)
{
    UserDefault::getInstance()->setIntegerForKey(OPENGL_HEIGHT, h);
    UserDefault::getInstance()->flush();
}

int UserDataManager::getOpenGLHeight()
{
    return UserDefault::getInstance()->getIntegerForKey(OPENGL_HEIGHT, 640);
}

void UserDataManager::setIsDebug(bool isDebug)
{
    UserDefault::getInstance()->setIntegerForKey(ISDEBUG, isDebug);
    UserDefault::getInstance()->flush();
}

bool UserDataManager::getIsDebug()
{
    return UserDefault::getInstance()->getIntegerForKey(ISDEBUG, false);
}


