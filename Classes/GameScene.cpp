//
//  GameScene.cpp
//  FlappyBird
//
//  Created by 夏旸 on 16/7/19.
//
//

#include "GameScene.h"
#include "BackgroundLayer.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Scene *GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, -900));
    
    auto backgroundLayer = BackgroundLayer::create();
    scene->addChild(backgroundLayer);

    auto layer = GameScene::create();
    layer->gameScene = scene;
    
    scene->addChild(layer);
    
    return scene;
}

GameScene::GameScene(){}
GameScene::~GameScene(){}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size visiableSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    this->gameStatus = GAME_STATUS_READY;
    this->score = 0;
    
    this->bird = BirdSprite::getInstance();
    this->bird->createBird();
    PhysicsBody *body = PhysicsBody::create();
    body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
    body->setDynamic(true);
    body->setLinearDamping(.0f);
    body->setGravityEnable(false);
    this->bird->setPhysicsBody(body);
    this->bird->setPosition(origin.x + visiableSize.width*1/3-5, origin.y + visiableSize.height/2+5);
    this->bird->idle();
    this->addChild(this->bird);
    
    this->groundNode = Node::create();
    
    float landHeight = BackgroundLayer::getLandHeight();
    auto groundBody = PhysicsBody::create();
    groundBody->addShape(PhysicsShapeBox::create(Size(288, landHeight)));
    groundBody->setDynamic(false);
    groundBody->setLinearDamping(0.0f);
    this->groundNode->setPhysicsBody(groundBody);
    this->groundNode->setPosition(144, landHeight/2);
    this->addChild(this->groundNode);
    
    this->landSprite1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
    this->landSprite1->setAnchorPoint(Point::ZERO);
    this->landSprite1->setPosition(Point::ZERO);
    this->addChild(this->landSprite1, 30);

    this->landSprite2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
    this->landSprite2->setAnchorPoint(Point::ZERO);
    this->landSprite2->setPosition(this->landSprite1->getContentSize().width-2.0f,0);
    this->addChild(this->landSprite2, 30);
    
    this->shiftLand = schedule_selector(GameScene::scrollLand);
    this->schedule(this->shiftLand, 0.01f);
    this->scheduleUpdate();
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

bool GameScene::onContactBegin(const PhysicsContact& contact) {
    this->gameOver();
    return true;
}

void GameScene::scrollLand(float dt){
    this->landSprite1->setPositionX(this->landSprite1->getPositionX() - 2.0f);
    this->landSprite2->setPositionX(this->landSprite1->getPositionX() + this->landSprite1->getContentSize().width - 2.0f);
    if(this->landSprite2->getPositionX() == 0) {
        this->landSprite1->setPositionX(0);
    }
    
    // move the pips
    for (auto singlePip : this->pips) {
        singlePip->setPositionX(singlePip->getPositionX() - 2);
        if(singlePip->getPositionX() < -PIP_WIDTH) {
            singlePip->setTag(PIP_NEW);
            Size visibleSize = Director::getInstance()->getVisibleSize();
            singlePip->setPositionX(visibleSize.width);
            singlePip->setPositionY(this->getRandomHeight());
        }
    }
}

void GameScene::onTouch() {
    if(this->gameStatus == GAME_STATUS_OVER) {
        return;
    }
    
    SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
    if(this->gameStatus == GAME_STATUS_READY) {
//        this->delegator->onGameStart();
        this->bird->fly();
        this->gameStatus = GAME_STATUS_START;
        this->createPips();
    }else if(this->gameStatus == GAME_STATUS_START) {
        this->bird->getPhysicsBody()->setVelocity(Vect(0, 260));
    }
}

void GameScene::rotateBird() {
    float verticalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
    this->bird->setRotation(MIN(MAX(-90, (verticalSpeed*0.2 + 60)), 30));
}


void GameScene::update(float delta) {
    if (this->gameStatus == GAME_STATUS_START) {
        this->rotateBird();
        this->checkHit();
    }
}

void GameScene::createPips() {
    // Create the pips
    for (int i = 0; i < PIP_COUNT; i++) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Sprite *pipUp = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up"));
        Sprite *pipDown = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down"));
        Node *singlePip = Node::create();
        
        // bind to pair
        pipDown->setPosition(0, PIP_HEIGHT + PIP_DISTANCE);
        singlePip->addChild(pipDown, 0, DOWN_PIP);
        singlePip->addChild(pipUp, 0, UP_PIP);
        singlePip->setPosition(visibleSize.width + i*PIP_INTERVAL + WAIT_DISTANCE, this->getRandomHeight());
        auto body = PhysicsBody::create();
        auto shapeBoxDown = PhysicsShapeBox::create(pipDown->getContentSize(),PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, PIP_HEIGHT + PIP_DISTANCE));
        body->addShape(shapeBoxDown);
        body->addShape(PhysicsShapeBox::create(pipUp->getContentSize()));
        body->setDynamic(false);
        singlePip->setPhysicsBody(body);
        singlePip->setTag(PIP_NEW);
        
        this->addChild(singlePip);
        this->pips.push_back(singlePip);
    }
}

int GameScene::getRandomHeight() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return rand()%(int)(2*PIP_HEIGHT + PIP_DISTANCE - visibleSize.height);
}

void GameScene::checkHit() {
    for(auto pip : this->pips) {
        if (pip->getTag() == PIP_NEW) {
            if (pip->getPositionX() < this->bird->getPositionX()) {
                SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
                this->score ++;
//                this->delegator->onGamePlaying(this->score);
                pip->setTag(PIP_PASS);
            }
        }
    }
}

void GameScene::gameOver() {
    if(this->gameStatus == GAME_STATUS_OVER) {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");
    /*
    //get the best score
    int bestScore = UserRecord::getInstance()->readIntegerFromUserDefault("best_score");
    //update the best score
    if(this->score > bestScore){
        UserRecord::getInstance()->saveIntegerToUserDefault("best_score",this->score);
    }
    this->delegator->onGameEnd(this->score, bestScore);
     */
    this->unschedule(shiftLand);
    SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
    this->bird->die();
    this->bird->setRotation(-90);
    this->birdSpriteFadeOut();
    this->gameStatus = GAME_STATUS_OVER;
}

void GameScene::birdSpriteFadeOut(){
    FadeOut* animation = FadeOut::create(1.5);
    CallFunc* animationDone = CallFunc::create(bind(&GameScene::birdSpriteRemove,this));
    Sequence* sequence = Sequence::createWithTwoActions(animation,animationDone);
    this->bird->stopAllActions();
    this->bird->runAction(sequence);
}

void GameScene::birdSpriteRemove(){
    this->bird->setRotation(0);
    this->removeChild(this->bird);
}
