//
//  UserRecord.hpp
//  FlappyBird
//
//  Created by 夏旸 on 16/7/23.
//
//

#ifndef UserRecord_h
#define UserRecord_h

#include "cocos2d.h"

USING_NS_CC;

class UserRecord : public Object
{
public:
    static UserRecord *getInstance();
    static void destroyInstance();
    UserRecord();
    ~UserRecord();
    virtual bool init();
    int readIntegerFromUserDefault(const char *key);
    void saveIntegerToUserDefault(const char *key, int score);
private:
    static UserRecord *sharedUserRecord;
};

#endif /* UserRecord_hpp */
