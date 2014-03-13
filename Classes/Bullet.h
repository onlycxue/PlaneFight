#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"

//�ӵ���
class Bullet:public cocos2d::CCSprite
{
public:
	virtual bool initWithFile(const char* fileName,int lethality);
protected:
	//�����ӵ���ɱ����
	CC_SYNTHESIZE(int, _lethality,Lethality);
};

class YellowBullet :public Bullet
{
public:
	virtual bool init(void);
	CREATE_FUNC(YellowBullet);
};

class BlueBullet :public Bullet
{
public:
	virtual bool init(void);
	CREATE_FUNC(BlueBullet);
};

class GrayBullet :public Bullet
{
public:
	virtual bool init(void);
	CREATE_FUNC(GrayBullet);
};

#endif