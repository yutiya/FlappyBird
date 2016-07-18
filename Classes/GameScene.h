

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	virtual bool init();
	void restart();
	CREATE_FUNC(GameScene);
};


#endif