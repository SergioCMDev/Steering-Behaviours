#ifndef __KINEMATIC_FLEE_H__
#define __KINEMATIC_FLEE_H__ 1

#include <defines.h>

class KinematicFlee {

public:
	KinematicFlee() {}
	~KinematicFlee() {}

	void calculate(const KinematicStatus& character, const KinematicStatus *target, KinematicSteering *steering) {
		//going full speed towards the target
		steering->velocity = (character.position - target->position).normalized() * max_speed;
		steering->rotation = 0.0f;
	}
private:
	const float max_speed = 100.0f;
};
#endif
