#pragma once
#include "./CoinBarSprite.h"

#define GOLD_COIN_ID 142
#define SILVER_COIN_ID 1329
#define COINS_CONTAINER_TAG 800
class CoinsProgressbarManager {
	static CoinsProgressbarManager* instance;
	CCNode* coinsContainer;

	std::vector<std::pair<CoinBarSprite*, GameObject*>> coins;

	void recreate(CCSprite* bar, CCArray* objects) {
		coins.clear();
		coinsContainer = CCNode::create();
		bar->addChild(coinsContainer);
		coinsContainer->setTag(COINS_CONTAINER_TAG);

		redefineCoinsAndCoinRefs(bar->getContentHeight(), objects);
	}

	void redefineCoinsAndCoinRefs(float barHeight, CCArray* objects) {// call only from recreate
		CCObject* obj;
		CCARRAY_FOREACH(objects, obj) {
			auto block = static_cast<GameObject*>(obj);
			if (block->m_objectID == GOLD_COIN_ID || block->m_objectID == SILVER_COIN_ID) {
				auto coin = CoinBarSprite::create(block->m_objectID == GOLD_COIN_ID);
				coin->setPositionY(barHeight / 2.f);
				coinsContainer->addChild(coin);
				coins.push_back(std::make_pair(coin, block));
			}
		}
	}

public:
	void reset(PlayLayer* playLayer) {
		auto bar = playLayer->m_progressBar; // for 2.1 it was MBO(CCSprite*, self, 0x404)

		if (!bar->getChildByTag(COINS_CONTAINER_TAG))
			recreate(bar, playLayer->m_objects);	
	}

	void update(PlayLayer* playLayer) {	
		auto bar = playLayer->m_progressBar; // for 2.1 it was MBO(CCSprite*, self, 0x404)
		auto levelLength = playLayer->m_levelLength; //for 2.1 it was MBO(float, self, 0x3B4)

		for (int i = 0; i < coins.size(); i++) {
			auto pair = coins[i];
			pair.first->update(pair.second, bar->getContentWidth(), levelLength);
		}
	}

	static CoinsProgressbarManager* getInstance() {
		if (!instance)
			instance = new CoinsProgressbarManager;
		return instance;
	}
};
CoinsProgressbarManager* CoinsProgressbarManager::instance = nullptr;
