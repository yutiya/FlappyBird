//
//  LoadingScene.hpp
//  FlappyBird
//
//  Created by 夏旸 on 16/7/16.
//
//

#ifndef LoadingScene_h
#define LoadingScene_h

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class LoadingScene : public Scene
{
public:
    LoadingScene();
    ~LoadingScene();
    virtual bool init();
    CREATE_FUNC(LoadingScene);
    void OnEnter();
private:
    void loadingCallBack(Texture2D *texture);
};

#endif /* LoadingScene_h */
