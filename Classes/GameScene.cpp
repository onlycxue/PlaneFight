/*
 * =====================================================================================
 *
 *       Filename:  GameScene.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/21/2014 03:31:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "GameScene.h"

USING_NS_CC;

#define FIX_POS(_pos,_min,_max) \
if (_pos < _min)  \
_pos = _min;      \
else if (_pos > _max) \
_pos = _max; \

bool GameScene::init()
{
	if(!CCLayer::init())	
	{
		return false;	
	}

	setAccelerometerEnabled(true);
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	m_bgHeight = 800;
	m_bgSpeed = 4;

	m_bg1 = CCSprite::create("bg1.jpg"); 
	m_bg1->setAnchorPoint(ccp(0,0));
	m_bg1->setPosition(ccp(0,0));
	addChild(m_bg1,0);

	m_bg2 = CCSprite::create("bg2.jpg"); 
	m_bg2->setAnchorPoint(ccp(0,0));
	m_bg2->setPosition(ccp(0,m_bgHeight-1));
	addChild(m_bg2,0);
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plane0.plist");
	m_plane = CCSprite::create();
	bool w = m_plane->initWithSpriteFrameName("hero1.png");
	//CCLOG("#####################################\n");
	//CCLOG("#####################################\n");
	m_plane->setAnchorPoint(ccp(0.5, 0));
	m_plane->setPosition(ccp(size.width / 2, 0));
	addChild(m_plane);

	m_enemplaneArray = CCArray::create();
	m_enemplaneArray->retain();
	m_projectileArray = CCArray::create();
	m_projectileArray->retain();

	setTouchEnabled(true);
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene::gameLogic), 2);
	CCLog("init over");
	addEnemyPlane();
	return true;
	
}

CCScene* GameScene::scene()	
{
	CCScene* scene = CCScene::create();
	GameScene* layer = GameScene::create();
	scene->addChild(layer,1);	
	return scene;
}

void GameScene::update(float t)	
{
	ScrollBg();	
	collisionCheck();
}
void GameScene::gameLogic(float dt)
{
	addEnemyPlane();
}
void GameScene::ScrollBg()
{

	m_bgHeight = m_bgHeight - m_bgSpeed;

	if(m_bgHeight <= 0)
	{
		m_bgHeight = 800;	
	}

	m_bg1->setPosition(ccp(m_bg1->getPosition().x,m_bgHeight-800));
	m_bg2->setPosition(ccp(m_bg2->getPosition().x,m_bgHeight-1));

}
//添加敌机
void GameScene::addEnemyPlane()
{
	EnemyPlane* enemPlane = WeakEnemPlane::create();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minX = enemPlane->getContentSize().width / 2;
	int maxX = winSize.width - enemPlane->getContentSize().width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;
	//enemPlane->setPosition(ccp(winSize.width + enemPlane->getContentSize().width / 2, actualY));
	enemPlane->setPosition(ccp(actualX,winSize.height+enemPlane->getContentSize().height));

	int minDuration = enemPlane->getMinMoveDuration();
	int maxDuration = enemPlane->getMaxMoveDuration();
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand() % rangeDuration) + minDuration;

	CCMoveTo *actionMove = CCMoveTo::create(actualDuration, ccp(actualX, -enemPlane->getContentSize().width / 2));
	CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameScene::spriteMoveFinished));
	enemPlane->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));

	addChild(enemPlane);
	m_enemplaneArray->addObject(enemPlane);
}
void GameScene::didAccelerate(cocos2d::CCAcceleration* pAccelerationValue)
{
	CCDirector* pDir = CCDirector::sharedDirector();
	CCSize winSize = pDir->getWinSize();
	if (m_plane == NULL)
	{
		return;
	}
	CCSize planeSize = m_plane->getContentSize();
	CCPoint ptNow = m_plane->getPosition();
	CCPoint ptTemp = pDir->convertToUI(ptNow);
	ptTemp.x += pAccelerationValue->x * 29.81f;
	ptTemp.y -= pAccelerationValue->y * 29.81f;

	
	CCPoint ptNext = pDir->convertToGL(ptTemp);
	FIX_POS(ptNext.x, planeSize.width / 2, winSize.width - planeSize.width / 2);
	FIX_POS(ptNext.y, planeSize.height / 2, winSize.height - planeSize.height / 2);

	m_plane->setPosition(ptNext);

}
void GameScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* projectile = CCSprite::create("bullet.png");
	//projectile->retain();
	projectile->setPosition(ccp(m_plane->getPosition().x, m_plane->getPosition().y + m_plane->getContentSize().height / 2));
	projectile->setTag(2);
	CCMoveTo *actionMove = CCMoveTo::create(2, ccp(projectile->getPosition().x, winSize.height + m_plane->getContentSize().height / 2));
	CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameScene::spriteMoveFinished));
	projectile->runAction(CCSequence::create(actionMove, actionMoveDone,NULL));

	addChild(projectile);
	m_projectileArray->addObject(projectile);
}
void GameScene::collisionCheck()
{
	CCObject *pObject = NULL;
	CCObject *pObject2 = NULL;
	CCArray *projectileToDel = CCArray::create();
	CCARRAY_FOREACH(m_projectileArray, pObject)
	{
		CCSprite *projectile = (CCSprite*)pObject;
		bool enemplaneHit = false;
		CCArray *enemplaneToDel = CCArray::create();
		
		CCARRAY_FOREACH(m_enemplaneArray, pObject2)
		{
			EnemyPlane *plane = (EnemyPlane*)pObject2;
			//判断子弹是否与敌机相遇
			if (projectile->boundingBox().intersectsRect(plane->boundingBox()))
			{
				enemplaneHit = true;
				plane->setHp(plane->getHp() - 1);
				//没血了飞机消失
				if (plane->getHp()<= 0)
				{
					//this->removeChild(plane);
					//m_enemplaneArray->removeObject(plane);
					enemplaneToDel->addObject(plane);
				}
				break;
			}
		
		}
		//统计杀敌数目
		CCARRAY_FOREACH(enemplaneToDel, pObject2)
		{
			EnemyPlane *plane = (EnemyPlane*)pObject2;
			this->removeChild(plane);
			m_enemplaneArray->removeObject(plane);
			
			//num++;
		}
		enemplaneToDel->release();
		if (enemplaneHit)
		{
			projectileToDel->addObject(pObject);
		}
		enemplaneHit = false;
	}
	//让子弹消失
	CCARRAY_FOREACH(projectileToDel, pObject)
	{
		CCSprite* sprite = (CCSprite*)(pObject);
		removeChild(sprite);
		projectileToDel->removeObject(sprite);
	}
	projectileToDel->release();
}
void GameScene::spriteMoveFinished(CCNode *sender)
{
	CCSprite *sprite = (CCSprite*)sender;
	this->removeChild(sprite, true);
	if (sprite->getTag() == 1)
	{
		//其他处理
		this->m_enemplaneArray->removeObject(sprite);
	}
	else if (sprite->getTag() == 2)
	{
		m_projectileArray->removeObject(sprite);
	}

}