

#ifndef OptionLayer_h
#define OptionLayer_h

#include "cocos2d.h"

USING_NS_CC;

class OptionDelegate
{
public:
	virtual void onTouch() = 0;
};

class OptionLayer : public Layer
{
public:
	OptionLayer();
	~OptionLayer();

	virtual bool init();
	CREATE_FUNC(OptionLayer);

	void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);

	CC_SYNTHESIZE(OptionDelegate*, delegator, Delegator);
};


#endif
