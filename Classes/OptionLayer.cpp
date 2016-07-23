

#include "OptionLayer.h"

OptionLayer::OptionLayer(){}

OptionLayer::~OptionLayer(){}

bool OptionLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}


	return true;
}

void OptionLayer::onEnter()
{
    Layer::onEnter();
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchAllAtOnce::create();
    
    listener->onTouchesBegan = CC_CALLBACK_2(OptionLayer::onTouchesBegan, this);
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void OptionLayer::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}

void OptionLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
	this->delegator->onTouch();
}
