//
//  BirdSprite.cpp
//  FlappyBird
//
//  Created by 夏旸 on 16/7/16.
//
//

#include "BirdSprite.h"
#include "AtlasLoader.h"

BirdSprite::BirdSprite(){}

BirdSprite::~BirdSprite(){}

BirdSprite *BirdSprite::shareBirdSprite = nullptr;

BirdSprite *BirdSprite::getInstance()
{
	if (shareBirdSprite == NULL) {
		shareBirdSprite = new BirdSprite();
		if (!shareBirdSprite->init()) {
			delete shareBirdSprite;
			shareBirdSprite = NULL;
			CCLOG("ERROR: Could not init shareBirdSprite");

		}
	}
	return shareBirdSprite;
}

bool BirdSprite::init()
{
	this->isFirstTime = 3;
	return true;
}

Sprite* BirdSprite::createBird()
{
	this->createBirdByRandom();
	Sprite *birdSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(this->birdName));
	if (birdSprite)
	{
		Animation *animation = this->createAnimation(this->birdNameFormat.c_str(), 3, 10);
		Animate *animate = Animate::create(animation);
		this->idleAction = RepeatForever::create(animate);

		ActionInterval *up = MoveBy::create(0.4f, Point(0, 8));
		ActionInterval *upBack = up->reverse();
		this->swingAction = RepeatForever::create(Sequence::create(up, upBack, NULL));
		return birdSprite;
	}
	else {
		return NULL;
	}
}

void BirdSprite::idle(Sprite *birdSprite) {
	if (changeState(ACTION_STATE_IDLE)) {
		birdSprite->runAction(idleAction);
		birdSprite->runAction(swingAction);
	}
}

void BirdSprite::fly(Sprite *birdSprite) {
	if (changeState(ACTION_STATE_FLY)) {
		birdSprite->stopAction(swingAction);
	}
}

void BirdSprite::die(Sprite *birdSprite) {
	if (changeState(ACTION_STATE_DIE)) {
		birdSprite->stopAllActions();
	}
}

Animation *BirdSprite::createAnimation(const char *fmt, int count, float fps) {
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(1 / fps);
	for (int i = 0; i < count; i++){
		const char *filename = __String::createWithFormat(fmt, i)->getCString();
		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	return animation;
}

bool BirdSprite::changeState(ActionState state) {
	currentStatus = state;
	return true;
}

void BirdSprite::createBirdByRandom(){
	if (this->isFirstTime & 1){
		this->isFirstTime &= 2;
	}
	else if (this->isFirstTime & 2){
		this->isFirstTime &= 1;
		return;
	}
	srand((unsigned)time(NULL));
	int type = ((int)rand()) % 3;
	switch (type)
	{
	case 0:
		this->birdName = "bird0_0";
		this->birdNameFormat = "bird0_%d";
		break;
	case 1:
		this->birdName = "bird1_0";
		this->birdNameFormat = "bird1_%d";
		break;
	case 2:
		this->birdName = "bird2_0";
		this->birdNameFormat = "bird2_%d";
		break;
	default:
		this->birdName = "bird2_0";
		this->birdNameFormat = "bird2_%d";
		break;
	}
}
