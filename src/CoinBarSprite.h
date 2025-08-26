#pragma once
#include "./includes.h"

class CoinBarSprite : public CCSprite {
	CCSprite* activateSprite;

	virtual bool init(bool isGold) {
		if (!CCSprite::initWithSpriteFrameName(isGold ? "secretCoin_b_01_001.png" : "secretCoin_2_b_01_001.png")) return false;

		this->activateSprite = CCSprite::createWithSpriteFrameName(isGold ? "secretCoin_01_001.png" : "secretCoin_2_01_001.png");
		this->activateSprite->setPosition(this->getContentSize() / 2);
		this->addChild(activateSprite);

		this->setScale(0.3);
		return true;
	}
public:
	void update(GameObject* gameObjectRef, float barWidth, float levelLength) {
		auto coinPosition = gameObjectRef->m_positionX;
		this->setPositionX(coinPosition / levelLength * barWidth);
		this->activateSprite->setVisible(!gameObjectRef->hasBeenActivated());
	}
	static CoinBarSprite* create(bool isGold) {
		auto ret = new CoinBarSprite();
		if (ret && ret->init(isGold)) {
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
};
