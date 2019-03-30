#ifndef __COHESION_H__
#define __COHESION_H__ 1

#include<defines.h>
class Cohesion {
public:
	Cohesion() {}
	~Cohesion() {};

	virtual void calculate(const KinematicStatus* character1, const KinematicStatus* leader, Steering* steering) {
		//aceleration towards the target
		const MathLib::Vec2 newPosition = MathLib::Vec2();

		const MathLib::Vec2 directionToLeader = leader->position - character1->position;
		const float distance = directionToLeader.length();

		if (distance > MathLib::Vec2(MAX_DISTANCE_COHESION, MAX_DISTANCE_COHESION).length()) {
			const MathLib::Vec2 targetVelocity = directionToLeader.normalized() * max_speed;
			steering->linear = (targetVelocity - character1->velocity) + MathLib::Vec2(MAX_DISTANCE_COHESION, MAX_DISTANCE_COHESION) / time_to_taget;


			if (steering->linear.length() > max_acceleration_) {
				steering->linear = steering->linear.normalized() * max_acceleration_;
			}
		}


		steering->angular = 0.0f; //no angular
	}


private:
	const float max_acceleration_ = 5.0f;
	const float max_speed = 100.0f;
	const float time_to_taget = 1.0f;
};
#endif