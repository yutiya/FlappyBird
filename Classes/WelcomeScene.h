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

USING_NS_CC;
using namespace std;

class WelcomeScene : public Scene
{
public:
    WelcomeScene();
    ~WelcomeScene();
    bool virtual init();
    CREATE_FUNC(WelcomeScene);
};

#endif /* WelcomeScene_h */
