#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_
#include "cocos2d.h"

class GameOver:public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene(int num);
	void setScore(int num);
	void restartCallBack(cocos2d::CCObject* sender);
	CREATE_FUNC(GameOver);
private:
	cocos2d::CCLabelBMFont *m_scoreLabel;
};

#endif