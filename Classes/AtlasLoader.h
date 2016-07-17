//
//  AtlasLoader.hpp
//  FlappyBird
//
//  Created by Meone on 16/7/16.
//
//

#ifndef AtlasLoader_h
#define AtlasLoader_h

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

typedef struct _atlas {
    char name[255];
    int width;
    int height;
    Point start;
    Point end;
} Atlas;

class AtlasLoader {
public:
    static AtlasLoader *getInstance();
    
    static void destroyInstance();
    
    void loadAtlas(string filename);
    
    void loadAtlas(string filename, Texture2D *texture);
    
    SpriteFrame *getSpriteFrameByName(string name);
    
protected:
    AtlasLoader();
    
    virtual bool init();
    
    static AtlasLoader *sharedAtlasLoader;
    
    Map<std::string, SpriteFrame *> _spriteFrames;
};


#endif /* AtlasLoader_h */
