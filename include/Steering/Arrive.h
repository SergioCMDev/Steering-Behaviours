#ifndef __ARRIVE_H__
#define __ARRIVE_H__ 1

#include<defines.h>
class Arrive {
public:
	Arrive() {}
	~Arrive() {};

	virtual void calculate(const KinematicStatus& character, const KinematicStatus* target, Steering* steering) {
		//aceeleration towards the target

		//direction to the target
		const MathLib::Vec2 direction = target->position - character.position;
		const float distance = direction.length();
		float target_speed = max_speed;
		if (distance < slow_radius) {
			//speed slowing down
			target_speed = (max_speed * distance) / slow_radius;
		}
		//velocity towards the target
		const MathLib::Vec2 targetVelocity = direction.normalized() * target_speed;
		//linear acceleration adjust to time
		steering->linear = (targetVelocity - character.velocity) / time_to_taget;
		if (steering->linear.length() > max_acceleration_) {
			steering->linear = steering->linear.normalized() * max_acceleration_;
		}

		steering->angular = 0.0f; //no angular
	}

private:
	const float max_acceleration_ = 5.0f;
	const float max_speed = 100.0f;
	const float slow_radius = 100.0f;
	const float time_to_taget = 1.0f;
};
#endif