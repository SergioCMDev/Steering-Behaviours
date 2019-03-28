#ifndef __PURSUE_H__
#define __PURSUE_H__ 1

#include<defines.h>
#include<Steering/Seek.h>
#include<debug_draw.h>
class Pursue :public Seek{
public:
	Pursue() {}
	~Pursue() {};

	virtual void calculate(const KinematicStatus& character, const KinematicStatus* target, Steering* steering) {
		//distance to the target
		const float distance = (target->position - character.position).length();
		float speed = character.velocity.length(); //speed of character
		float prediction = max_prediction_; //max prediction
		if (speed > (distance / max_prediction_)) { //reasonable predicion
			prediction = distance / speed; //calc predicion time
		}
		KinematicStatus new_target = *target; //new target
		//position of new target
		new_target.position += target->velocity * prediction;
		DebugDraw::drawCross(new_target.position, 0x00, 0x00, 0xFF, 0xFF);
		//delegate to seek behavior with new target
		Seek::calculate(character, &new_target, steering);
	}

private:
	const float max_acceleration_ = 5.0f;
	const float max_prediction_ = 2.0f;

};
#endif



