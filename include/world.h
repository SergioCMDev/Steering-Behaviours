//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __WORLD_H__
#define __WORLD_H__ 1

#include <mathlib/vec2.h>
#include <defines.h>

#include <cstdio>
#include <agent.h>

using MathLib::Vec2;

class World {
public:
	World() {
		target_.init(this, Body::Color::Red, Body::Type::Manual);
		for (int i = 0; i < MAX_AGENTS; i++) {
			ia_[i].init(this, Body::Color::Green, Body::Type::Autonomous);
			ia_[i].getKinematic()->position = Vec2(WINDOW_WIDTH / (i + 1), WINDOW_HEIGHT / (i + 1));
		}
	};
	~World() {
		target_.shutdown();
		for (int i = 0; i < MAX_AGENTS; i++) {

			ia_[i].shutdown();
		}
	};

	void update(const float dt) {
		target_.update(dt);
		for (int i = 0; i < MAX_AGENTS; i++) {
			ia_[i].update(dt);
		}
	}
	void render() {
		target_.render();
		for (int i = 0; i < MAX_AGENTS; i++) {
			ia_[i].render();
		}
	}
	 static Agent* GetIAs() {
		return new Agent();
	}
	Agent* target() { return &target_; }
	Agent* ia(int i) { return &ia_[i]; }
private:
	Agent target_, ia_[MAX_AGENTS];
};

#endif