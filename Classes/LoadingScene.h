//
//  LoadingScene.hpp
//  FlappyBird
//
//  Created by Meone on 16/7/16.
//
//

#ifndef LoadingScene_h
#define LoadingScene_h

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class LoadingScene : public Layer
{
public:
	static cocos2d::Scene *createScene();

    LoadingScene();
    ~LoadingScene();
    virtual bool init();
    CREATE_FUNC(LoadingScene);
private:
    void loadingCallBack(Texture2D *texture);
};

#endif /* LoadingScene_h */
