//
//  WelcomeLayer.hpp
//  FlappyBird
//
//  Created by 夏旸 on 16/7/16.
//
//

#ifndef WelcomeLayer_h
#define WelcomeLayer_h

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "CCMenuItem.h"
#include "time.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

const int START_BUTTON_TAG = 100;

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
    
};

#endif /* WelcomeLayer_h */
