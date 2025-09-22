#include <Geode/Geode.hpp>

constexpr int GOLD = 142;
constexpr int SILVER = 1329;

using namespace geode::prelude;

#include <Geode/modify/PlayLayer.hpp>
class $modify(PlayLayer) {
	struct Fields {
		std::vector<std::pair<GameObject*, CCSprite*>> m_coinSprites;
	};

	void updateCoins() {
		for (auto [obj, sprite] : m_fields->m_coinSprites) {
			sprite->setPositionX(obj->getPositionX() / m_levelLength * m_progressBar->getContentWidth());
			sprite->setPositionY(m_progressBar->getContentHeight() / 2.);

			auto cache = CCSpriteFrameCache::sharedSpriteFrameCache();
			sprite->setDisplayFrame(cache->spriteFrameByName(fmt::format(
				"secretCoin{}{}_01_001.png",
				obj->m_objectID == SILVER ? "_2" : "",
				obj->m_isDisabled ? "_b" : ""
			).c_str()));
;		}
	}

	void setupHasCompleted() {
		PlayLayer::setupHasCompleted();

		for (auto& obj : CCArrayExt<GameObject>(m_objects)) {
			if (obj->m_objectID == GOLD || obj->m_objectID == SILVER) {
				auto sprite = CCSprite::createWithSpriteFrameName("secretCoin_01_001.png");
				sprite->setScale(0.3);
				m_progressBar->addChild(sprite);
				m_fields->m_coinSprites.push_back({obj, sprite});
			}
		}

		updateCoins();
	}

	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);
		updateCoins();
	}
};
