//
//  UserRecord.cpp
//  FlappyBird
//
//  Created by 夏旸 on 16/7/23.
//
//

#include "UserRecord.h"


UserRecord::UserRecord(){}
UserRecord::~UserRecord(){}

UserRecord *UserRecord::sharedUserRecord = nullptr;

UserRecord *UserRecord::getInstance()
{
    if (sharedUserRecord == NULL) {
        sharedUserRecord = new UserRecord();
        if (!sharedUserRecord->init()) {
            delete sharedUserRecord;
            sharedUserRecord = NULL;
            CCLOG("ERROR: Could not init sharedInstance");
        }
    }
    
    return sharedUserRecord;
}

void UserRecord::destroyInstance()
{
    CC_SAFE_DELETE(sharedUserRecord);
}

bool UserRecord::init()
{
    return true;
}
int UserRecord::readIntegerFromUserDefault(const char *key)
{
    return UserDefault::getInstance()->getIntegerForKey(key);
}

void UserRecord::saveIntegerToUserDefault(const char *key, int score)
{
    int oldScore = UserDefault::getInstance()->getIntegerForKey(key);
    if (score > oldScore) {
        UserDefault::getInstance()->setIntegerForKey(key, score);
    }
}
