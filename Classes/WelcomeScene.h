//
//  WelcomeScene.hpp
//  FlappyBird
//
//  Created by Meone on 16/7/16.
//
//

#ifndef WelcomeScene_h
#define WelcomeScene_h

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "BirdSprite.h"

USING_NS_CC;
using namespace std;


const int START_BUTTON_TAG = 998;

class WelcomeScene : public Layer
{
public:
    static Scene *createScene();
    
    WelcomeScene();
    ~WelcomeScene();
    virtual bool init();
    CREATE_FUNC(WelcomeScene);
private:
    void menuStartCallback(Ref *sender);
    void scrollLand(float dt);
    
    Sprite *land1;
    Sprite *land2;

    BirdSprite *bird;
};

#endif /* WelcomeScene_h */
