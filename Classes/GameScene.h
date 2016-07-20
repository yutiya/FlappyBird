

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "define.h"
#include "BirdSprite.h"
#include "OptionLayer.h"

USING_NS_CC;
using namespace std;

typedef enum _game_status {
    GAME_STATUS_READY = 1,
    GAME_STATUS_START,
    GAME_STATUS_OVER,
} GameStatus;

class StatusDelegate {
public:
    virtual void onGameStart() = 0;
    virtual void onGamePlaying(int score) = 0;
    virtual void onGameEnd(int curScore, int bestScore) = 0;
};

class GameScene : public Layer, public OptionDelegate
{
public:
    static Scene *createScene();
    
	GameScene();
	~GameScene();
	virtual bool init();
	void restartGame();
	CREATE_FUNC(GameScene);
	void onTouch();
    void update(float delta);
	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);
private:
    Scene *gameScene;
    void rotateBird();
    void createPips();
    int getRandomHeight();
    void checkHit();
    void birdSpriteFadeOut();
    void birdSpriteRemove();
    PhysicsWorld *world;
    GameStatus gameStatus;
    int score;
    BirdSprite *bird;
    Node *groundNode;
    vector<Node *> pips;
    Sprite *landSprite1, *landSprite2;
    SEL_SCHEDULE shiftLand;
    void scrollLand(float dt);
    bool onContactBegin(const PhysicsContact &contact);
    void gameOver();
};


#endif