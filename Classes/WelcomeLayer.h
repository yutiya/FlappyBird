//
//  WelcomeLayer.hpp
//  FlappyBird
//
//  Created by Meone on 16/7/16.
//
//

#ifndef WelcomeLayer_h
#define WelcomeLayer_h

#include "cocos2d.h"
#include "BirdSprite.h"

USING_NS_CC;


const int START_BUTTON_TAG = 998;

class WelcomeLayer : public Layer
{
public:
    WelcomeLayer();
    ~WelcomeLayer();
    virtual bool init();
    CREATE_FUNC(WelcomeLayer);
private:
    void menuStartCallback(Object *sender);
    
    void scrollLand(float dt);
    
    Sprite *land1;
    Sprite *land2;
    
	BirdSprite *bird;
};

#endif /* WelcomeLayer_h */
