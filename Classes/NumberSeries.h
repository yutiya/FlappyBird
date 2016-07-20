

#ifndef NumberSeries_h
#define NumberSeries_h

#include "cocos2d.h"
#include "AtlasLoader.h"

USING_NS_CC;
using namespace std;

typedef enum _gravity {
	GRAVITY_CENTER = 1,
	GRAVITY_LEFT,
	GRAVITY_RIGHT,
} Gravity;

const int NumberInterval = 4;

class NumberSeries : public Object
{
public:
	NumberSeries();
	~NumberSeries();
	virtual bool init();
	CREATE_FUNC(NumberSeries);
	void loadNumber(const char *fmt, int base = 0);
	SpriteFrame *at(int index);
private:
	vector<SpriteFrame *> numberSeries;
};

#endif

#ifndef Number_h
#define Number_h

class Number
{
public:
	static Number *getInstance();
	static void destroyInstance();
	Number();
	~Number();
	virtual bool loadNumber(const char *name, const char *fmt, int base = 0);
	Node *convert(const char *name, int number, Gravity gravity = Gravity::GRAVITY_CENTER);
	virtual bool init();
private:
	Map<string, NumberSeries *> numberContainer;
	static Number *sharedNumber;
};

#endif