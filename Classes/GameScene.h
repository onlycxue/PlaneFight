#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"
#include "EnemyPlane.h"
class GameScene:public cocos2d::CCLayer
{
public:
	virtual bool init();
	void update(float t);	
	static cocos2d::CCScene* scene();
	void addEnemyPlane();
	void gameLogic(float dt);
	void spriteMoveFinished(CCNode *sender);

	virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
	void collisionCheck();
	//接受点击发送子弹
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	CREATE_FUNC(GameScene);

private:
	void ScrollBg();
	cocos2d::CCSprite *m_bg1;
	cocos2d::CCSprite *m_bg2;
	cocos2d::CCSprite *m_plane;
	cocos2d::CCArray  *m_enemplaneArray;
	cocos2d::CCArray  *m_projectileArray;
	int m_bgHeight;
	int m_bgSpeed;


};

#endif
