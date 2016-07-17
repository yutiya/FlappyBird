//
//  LoadingScene.cpp
//  FlappyBird
//
//  Created by Meone on 16/7/16.
//
//

#include "LoadingScene.h"
#include "WelcomeScene.h"

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoadingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

LoadingScene::LoadingScene(){}
LoadingScene::~LoadingScene(){}



bool LoadingScene::init()
{
    if (!Layer::init()) {
        return false;
    }
	Sprite *background = Sprite::create("splash.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	background->setPosition(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2);
	this->addChild(background);

	Director::getInstance()->getTextureCache()->addImageAsync("atlas.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	return true;
}

void LoadingScene::loadingCallBack(cocos2d::Texture2D *texture)
{
    AtlasLoader::getInstance()->loadAtlas("atlas.txt", texture);
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");
    
	auto scene = WelcomeScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}
