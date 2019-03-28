#ifndef __SEPARATION_H__
#define __SEPARATION_H__ 1

#include<defines.h>
class Separation {
public:
	Separation() {}
	~Separation() {};

	virtual void calculate(const KinematicStatus& character, const KinematicStatus* target, Steering* steering) {
		//aceleration towards the target
		steering->linear = (character.position - target->position).normalized() *	max_acceleration_;
		steering->angular = 0.0f; //no angular
	}

private:
	const float max_acceleration_ = 5.0f;

};
#endif