#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "cocos2d.h"

class GameScene:public cocos2d::CCLayer
{
public:
	virtual bool init();
	void update(float t);	
	static cocos2d::CCScene* scene();
	virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);

	CREATE_FUNC(GameScene);

private:
	void ScrollBg();
	cocos2d::CCSprite *m_bg1;
	cocos2d::CCSprite *m_bg2;
	cocos2d::CCSprite *m_plane;
	int m_bgHeight;
	int m_bgSpeed;


};

#endif
