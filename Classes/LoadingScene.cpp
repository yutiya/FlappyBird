//
//  LoadingScene.cpp
//  FlappyBird
//
//  Created by 夏旸 on 16/7/16.
//
//

#include "LoadingScene.h"

LoadingScene::LoadingScene(){}
LoadingScene::~LoadingScene(){}

bool LoadingScene::init()
{
    if (Scene::init()) {
        return true;
    } else {
        return false;
    }
}

void LoadingScene::OnEnter()
{
    Sprite *background = Sprite::create("splash.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    background->setPosition(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2);
    this->addChild(background);
    
    Director::getInstance()->getTextureCache()->addImageAsync("atlas.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
}

void LoadingScene::loadingCallBack(cocos2d::Texture2D *texture)
{
    AtlasLoader::getInstance()->loadAtlas("atlas.txt", texture);
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");
    
}
