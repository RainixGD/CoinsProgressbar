#include "./CoinsProgressbarManager.h"

#include <Geode/modify/PlayLayer.hpp>
class $modify(PlayLayer) {
	void resetLevel() {
		PlayLayer::resetLevel();
		CoinsProgressbarManager::getInstance()->reset(this);
	}
	void postUpdate(float dt) {
		CoinsProgressbarManager::getInstance()->update(this);
		PlayLayer::postUpdate(dt);
	}
};
