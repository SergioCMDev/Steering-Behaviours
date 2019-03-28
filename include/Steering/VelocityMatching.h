#ifndef __VELOCITY_MATCHING_H__
#define __VELOCITY_MATCHING_H__ 1

#include<defines.h>
class VelocityMatching {
public:
	VelocityMatching() {}
	~VelocityMatching() {};

	virtual void calculate(const KinematicStatus& character, const KinematicStatus* target, Steering* steering) {
		//linear acceleration adjusted to time
		steering->linear = (target->velocity - character.velocity) / time_to_target_;
		if (steering->linear.length() > max_acceleration_) { //max out
		//normalized to max acceleration
			steering->linear = steering->linear.normalized() * max_acceleration_;
		}
	}

private:
	const float max_acceleration_ = 5.0f;
	const float time_to_target_ = 5.0f;

};
#endif