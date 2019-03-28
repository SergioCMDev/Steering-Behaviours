#ifndef __KINEMATIC_SEEK_H__
#define __KINEMATIC_SEEK_H__ 1

#include <defines.h>

class KinematicSeek {

public:
	KinematicSeek() {}
	~KinematicSeek() {}

	void calculate(const KinematicStatus& character, const KinematicStatus *target, KinematicSteering* steering) {
		//going full speed towards the target
		steering->velocity = (target->position - character.position).normalized() * max_speed;
		steering->rotation = 0.0f;
	}
private:
	const float max_speed = 100.0f;
};
#endif