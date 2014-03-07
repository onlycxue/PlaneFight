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
	
	m_plane = CCSprite::create("plane_72x72.png");
	m_plane->setAnchorPoint(ccp(0.5, 0));
	m_plane->setPosition(ccp(size.width / 2, 0));
	addChild(m_plane);
	this->scheduleUpdate();
	CCLog("init over");
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
