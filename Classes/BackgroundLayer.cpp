

#include "BackgroundLayer.h"
#include "AtlasLoader.h"

BackgroundLayer::BackgroundLayer(){}
BackgroundLayer::~BackgroundLayer(){}

bool BackgroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	time_t t = time(NULL);
	tm *lt = localtime(&t);
	int hour = lt->tm_hour;
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

	return true;
}

float BackgroundLayer::getLandHeight()
{
	return Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"))->getContentSize().height;
}