//
//  WelcomeLayer.cpp
//  FlappyBird
//
//  Created by Meone on 16/7/16.
//
//

#include "WelcomeLayer.h"
#include "CCMenu.h"
#include "CCMenuItem.h"
#include "SimpleAudioEngine.h"
#include "time.h"
#include "AtlasLoader.h"

USING_NS_CC;
using namespace CocosDenshion;

WelcomeLayer::WelcomeLayer(){};
WelcomeLayer::~WelcomeLayer(){};

bool WelcomeLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	time_t t = time(NULL);
	tm *lt = localtime(&t);
	int hour = lt->tm_hour;
	//背景
	Sprite *background;
	if (hour >= 6 && hour <= 17)
	{
		background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_day"));
	} else {
		background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_night"));
	}
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	this->addChild(background);
	//标题
	Sprite *title = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("title"));
	title->setPosition(Point(origin.x + visiableSize.width / 2, (visiableSize.height * 5) / 7));
	this->addChild(title);
	//点击按钮
	Sprite *startButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite *activeStartButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	activeStartButton->setPositionY(5);
	//开始按钮
	auto menuItem = MenuItemSprite::create(startButton, activeStartButton, NULL, CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this));
	menuItem->setPosition(Point(origin.x + visiableSize.width / 2, origin.y + visiableSize.height * 2 / 5));
	//开始菜单
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Point(origin.x, origin.y));
	this->addChild(menu, 1);
	//地板
	this->land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->land1->setAnchorPoint(Point::ZERO);
	this->land1->setPosition(Point::ZERO);
	this->addChild(this->land1);
	//相同地板
	this->land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->land2->setAnchorPoint(Point::ZERO);
	this->land2->setPosition(this->land1->getContentSize().width - 2.0f, 0);
	this->addChild(this->land2);
	//地板不断运动
	this->schedule(schedule_selector(WelcomeLayer::scrollLand), 0.01f);
	//版权
	Sprite *copyright = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("brand_copyright"));
	copyright->setPosition(Point(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 6));
	this->addChild(copyright, 10);
	//飞翔小鸟
	this->bird = BirdSprite::getInstance();
	this->bird->createBird();
	this->bird->setTag(BIRD_SPRITE_TAG);
	this->bird->setPosition(Point(origin.x + visiableSize.width / 2, origin.y + visiableSize.height * 3 / 5 - 10));
	this->bird->idle();
	this->addChild(this->bird);

	return true;
}

void WelcomeLayer::scrollLand(float dt){
	this->land1->setPositionX(this->land1->getPositionX() - 2.0f);
	this->land2->setPositionX(this->land1->getPositionX() + this->land1->getContentSize().width - 2.0f);

	if (this->land2->getPositionX() == 0) {
		this->land1->setPositionX(0);
	}
}

void WelcomeLayer::menuStartCallback(Object *sender)
{
	CCLOG("MenuItem Clicked");
}