//
//  StatusLayer.hpp
//  FlappyBird
//
//  Created by 夏旸 on 16/7/19.
//
//

#ifndef StatusLayer_h
#define StatusLayer_h

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "GameScene.h"
#include <string>

USING_NS_CC;
using namespace std;

const string NUMBER_SCORE = "number_score";
const string NUMBER_FONT = "font";
const int CURRENT_SCORE_SPRITE_TAG = 10001;

class StatusLayer : public Layer, public StatusDelegate
{
public:
    StatusLayer();
    ~StatusLayer();
    virtual bool init();
    CREATE_FUNC(StatusLayer);
    
    void onGameStart();
    
    void onGamePlaying(int score);
    
    void onGameEnd(int curScore, int bestScore);
    
private:
    void showReadyStatus();
    
    void showStartStatus();
    
    void showOverStatus(int curScore, int bestScore);
    
    void loadWhiteSprite();
    
    void blinkFullScreen();
    
    void fadeInGameOver();
    
    void jumpToScorePanel();
    
    void fadeInRestartBtn();
    
    void refreshScoreCallback();
    
    void refreshScoreExecutor(float dt);
    
    string getMedalsName(int score);
    
    Sprite* blink;
    
    void setBlinkSprite();
    
    void blinkAction();
    
    void menuRestartCallback(Object *sender);
    
    Sprite *scoreSprite;
    
    Sprite *getreadySprite;
    
    Sprite *tutorialSprite;
    
    Sprite *whiteSprite;
    
    int currentScore;
    
    int bestScore;
    
    int tmpScore;
    
    bool isNewRecord;
    
    Point originPoint;
    
    Size visibleSize;
};

#endif /* StatusLayer_h */
