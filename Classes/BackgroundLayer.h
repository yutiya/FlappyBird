

#ifndef BackgroundLayer_h
#define BackgroundLayer_h

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class BackgroundLayer : public Layer
{
public:
	static float getLandHeight();
	BackgroundLayer();
	~BackgroundLayer();
	virtual bool init();
	CREATE_FUNC(BackgroundLayer);
};




#endif