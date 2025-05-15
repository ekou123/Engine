#pragma once
#include <memory>

class Actor;

class Component {
public:
	virtual ~Component() = default;
	void setOwner(Actor* actor) { this->owner = actor; }
	virtual void init() {}
	virtual void update(float dt) {
		if (!enabled) {
			return;
		}
	}
	
	void enable() {
		enabled = true;
	}
	virtual void disable() {
		enabled = false;
	}

protected:
	bool enabled = true;
	Actor* owner = nullptr;
};
