

#include "GameScene.h"
#include "BackgroundLayer.h"

GameScene::GameScene(){}
GameScene::~GameScene(){}

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	this->getPhysicsWorld()->setGravity(Vect(0, -900));

	auto backgroundLayer = BackgroundLayer::create();
	if (backgroundLayer)
	{
		this->addChild(backgroundLayer);
	}
	return true;
}

void GameScene::restart()
{
	this->removeAllChildrenWithCleanup(true);
	this->init();
}
