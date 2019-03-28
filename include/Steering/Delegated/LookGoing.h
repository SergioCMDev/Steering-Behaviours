#ifndef __LOOK_GOING_H__
#define __LOOK_GOING_H__ 1

#include<defines.h>
#include<Steering/Align.h>

class LookGoing : public Align {
public:
	LookGoing() {}
	~LookGoing() {};

	virtual void calculate(const KinematicStatus& character, const KinematicStatus* target, Steering* steering) {
		//aceeleration towards the target
		if (character.velocity.length() == 0) {
			steering->angular = 0.0f;
			return;
		}
		KinematicStatus new_target = *target;
		//orientation of the new target facing velocity
		new_target.orientation = atan2(character.velocity.y(), character.velocity.x());

		//delegate to align behaviour with new target
		Align::calculate(character, &new_target, steering);

	}
};
#endif