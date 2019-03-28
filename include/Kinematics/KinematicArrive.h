
#ifndef __KINEMATIC_ARRIVE_H__
#define __KINEMATIC_ARRIVE_H__ 1

#include <defines.h>

class KinematicArrive {

public:
	KinematicArrive() {}
	~KinematicArrive() {}

	void calculate(const KinematicStatus& character, const KinematicStatus *target, KinematicSteering *steering) {
		//direction to the target
		steering->velocity = (target->position - character.position);
		if (steering->velocity.length2() < sq_radius_) {
			//inside the radius
			steering->velocity.x() = 0.0f;
			steering->velocity.y() = 0.0f;
		}
		else {
			steering->velocity /= time_to_target;
			if (steering->velocity.length() > max_speed) {
				//Normalized direction to max speed
				steering->velocity = steering->velocity.normalized() * max_speed;
			}
		}
	}
private:
	const float max_speed = 100.0f;
	const float sq_radius_ = 25.0f;
	const float time_to_target = 0.5f;
};
#endif