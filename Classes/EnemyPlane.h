#pragma once
#include "cocos2d.h"

class EnemyPlane : public cocos2d::CCSprite
{
public:
	//ͨ��֡������ؾ���ͼƬ
	virtual bool initWithFile(const char *frameName, int hp, int minMoveDuration, int maxMoveDuration);
	
protected:
	//�л���Ѫ
	CC_SYNTHESIZE(int, _hp, Hp);
	//�л�������ʱ�� ÿ���л����ֵ��ٶȲ�ȷ����
	CC_SYNTHESIZE(int, _minMoveDuration, MinMoveDuration);
	CC_SYNTHESIZE(int, _maxMoveDuration, MaxMoveDuration);
};

class WeakEnemPlane : public EnemyPlane
{
public:
	virtual bool init(void);
	CREATE_FUNC(WeakEnemPlane);
};

class StrongEnemPlane : public EnemyPlane
{
public:
	virtual bool init(void);
	CREATE_FUNC(StrongEnemPlane);
};

