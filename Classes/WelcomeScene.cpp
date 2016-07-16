//
//  WelcomeScene.cpp
//  FlappyBird
//
//  Created by 夏旸 on 16/7/16.
//
//

#include "WelcomeScene.hp"

WelcomeScene::WelcomeScene(){}

WelcomeScene::~WelcomeScene(){}

bool WelcomeScene::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!Scene::init());
        auto _welcomeLayer = WelcomeLayer::create();
        CC_BREAK_IF(!_welcomeLayer);
        this->addChild(_welcomeLayer);
        bRet = true;
    } while (0);
    return bRet;
}