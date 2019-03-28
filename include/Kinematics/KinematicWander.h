#ifndef __KINEMATIC_WANDER_H__
#define __KINEMATIC_WANDER_H__ 1

#include <defines.h>

class KinematicWander {

public:
	KinematicWander() {}
	~KinematicWander() {}

	void calculate(const KinematicStatus& character, const KinematicStatus *target, KinematicSteering *steering) {
		MathLib::Vec2 orientation;
		//orientation of character as vector
		orientation.fromPolar(1.0f, character.orientation);

		steering->velocity = orientation * max_speed; //max speed
		//rotate to random (binomial distriburion around 0)
		steering->rotation = max_rotation * (randomFloat(0.0f, 1.0f) - randomFloat(0.0f, 1.0f));
	}
private:
	const float max_speed = 100.0f;
	const float max_rotation = 3.14f;
};
#endif