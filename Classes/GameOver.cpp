#include "GameOver.h"
#include "GameScene.h"
USING_NS_CC;

bool GameOver::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg = CCSprite::create("gameover.png");
	bg->setPosition(ccp(winSize.width/2, winSize.height /2));
	addChild(bg, 0);

	m_scoreLabel = CCLabelBMFont::create("0", "fonts/konqa32.fnt");
	m_scoreLabel->setPosition(ccp(winSize.width / 2+50, winSize.height / 2 + 100));
	addChild(m_scoreLabel);

	CCMenuItemFont *item = CCMenuItemFont::create("restart", this, menu_selector(GameOver::restartCallBack));

	item->setFontSizeObj(40);
	item->setFontName("comic");
	item->setColor(cocos2d::ccc3(0, 0, 0));

	CCMenu* menu = CCMenu::create(item, NULL);
	menu->setPosition(ccp(winSize.width / 2 , winSize.height / 2-50));
	addChild(menu);
	return true;
}

void GameOver::setScore(int num)
{
	char str[10];
	sprintf(str, "%d", num);
	m_scoreLabel->setString(str);
}
CCScene* GameOver::scene(int num)
{
	CCLog("############in scene###############");
	CCScene* scene = CCScene::create();
	GameOver* layer = GameOver::create();
	layer->setScore(num);
	scene->addChild(layer, 1);
	CCLog("###########out scene#############");
	return scene;
}

void GameOver::restartCallBack(cocos2d::CCObject* sender)
{
	CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}