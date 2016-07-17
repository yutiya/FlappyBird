//
//  WelcomeScene.cpp
//  FlappyBird
//
//  Created by Meone on 16/7/16.
//
//

#include "WelcomeScene.h"
#include "WelcomeLayer.h"

WelcomeScene::WelcomeScene(){}

WelcomeScene::~WelcomeScene(){}

bool WelcomeScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto _welcomeLayer = WelcomeLayer::create();
	this->addChild(_welcomeLayer);
	return true;
}