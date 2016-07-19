//
//  WelcomeScene.cpp
//  FlappyBird
//
//  Created by Meone on 16/7/16.
//
//

#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "time.h"
#include "AtlasLoader.h"
#include "GameScene.h"

using namespace CocosDenshion;


Scene *WelcomeScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = WelcomeScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

WelcomeScene::WelcomeScene(){}

WelcomeScene::~WelcomeScene(){}

bool WelcomeScene::init()
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
    //±≥æ∞
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
    //±ÍÃ‚
    Sprite *title = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("title"));
    title->setPosition(Point(origin.x + visiableSize.width / 2, (visiableSize.height * 5) / 7));
    this->addChild(title);
    //µ„ª˜∞¥≈•
    Sprite *startButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
    Sprite *activeStartButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
    activeStartButton->setPositionY(5);
    //ø™ º∞¥≈•
    auto menuItem = MenuItemSprite::create(startButton, activeStartButton, NULL, CC_CALLBACK_1(WelcomeScene::menuStartCallback, this));
    menuItem->setPosition(Point(origin.x + visiableSize.width / 2, origin.y + visiableSize.height * 2 / 5));
    //ø™ º≤Àµ•
    auto menu = Menu::create(menuItem, NULL);
    menu->setPosition(Point(origin.x, origin.y));
    this->addChild(menu, 1);
    //µÿ∞Â
    this->land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
    this->land1->setAnchorPoint(Point::ZERO);
    this->land1->setPosition(Point::ZERO);
    this->addChild(this->land1);
    //œ‡Õ¨µÿ∞Â
    this->land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
    this->land2->setAnchorPoint(Point::ZERO);
    this->land2->setPosition(this->land1->getContentSize().width - 2.0f, 0);
    this->addChild(this->land2);
    //µÿ∞Â≤ª∂œ‘À∂Ø
    this->schedule(schedule_selector(WelcomeScene::scrollLand), 0.01f);
    //∞Ê»®
    Sprite *copyright = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("brand_copyright"));
    copyright->setPosition(Point(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 6));
    this->addChild(copyright, 10);
    //∑…œË–°ƒÒ
    this->bird = BirdSprite::getInstance();
    this->bird->createBird();
    this->bird->setTag(BIRD_SPRITE_TAG);
    this->bird->setPosition(Point(origin.x + visiableSize.width / 2, origin.y + visiableSize.height * 3 / 5 - 10));
    this->bird->idle();
    this->addChild(this->bird);
    
	return true;
}


void WelcomeScene::scrollLand(float dt){
    this->land1->setPositionX(this->land1->getPositionX() - 2.0f);
    this->land2->setPositionX(this->land1->getPositionX() + this->land1->getContentSize().width - 2.0f);
    
    if (this->land2->getPositionX() == 0) {
        this->land1->setPositionX(0);
    }
}

void WelcomeScene::menuStartCallback(Ref *sender)
{
    SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
    this->bird->stopAllActions();
    this->removeChildByTag(BIRD_SPRITE_TAG);
    
    auto scene = GameScene::createScene();
    TransitionScene *transition = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(transition);
}
