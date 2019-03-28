#ifndef __COHESION_H__
#define __COHESION_H__ 1

#include<defines.h>
class Cohesion {
public:
	Cohesion() {}
	~Cohesion() {};

	virtual void calculate(const KinematicStatus* character1, const KinematicStatus* character2, Steering* steering) {
		//aceleration towards the target
		for (size_t i = 0; i < MAX_AGENTS; i++)
		{
			steering->linear = (character1->position - character2->position + MathLib::Vec2(MAX_DISTANCE_COHESION, MAX_DISTANCE_COHESION));
			//target->position).normalized() *	max_acceleration_;
		}

		steering->angular = 0.0f; //no angular
	}

private:
	const float max_acceleration_ = 5.0f;

};
#endif