//
//  BirdSprite.hpp
//  FlappyBird
//
//  Created by 夏旸 on 16/7/16.
//
//

#ifndef BirdSprite_h
#define BirdSprite_h

#include "cocos2d.h"


USING_NS_CC;

typedef enum {
    ACTION_STATE_IDLE,
    ACTION_STATE_FLY,
    ACTION_STATE_DIE
} ActionState;

const int BIRD_SPRITE_TAG = 998;

class BirdSprite : public Sprite
{
public:
    BirdSprite();
    ~BirdSprite();
    static BirdSprite *getInstance();
    virtual bool init();
    bool createBird();
    void idle();
    void fly();
    void die();
protected:
    static Animation *createAnimation(const char *fmt, int count, float fps);
    void createBirdByRandom();
private:
    static BirdSprite *shareBirdSprite;
    bool changeState(ActionState state);
    Action *idleAction;
    Action *swingAction;
    ActionState currentStatus;
    std::string birdName;
    std::string birdNameFormat;
    unsigned int isFirstTime;
};



#endif /* BirdSprite_h */
