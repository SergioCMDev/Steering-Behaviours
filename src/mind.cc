//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#include <mind.h>
#include <body.h>
#include <world.h>

void Mind::init(World* world, Body* body) {
	world_ = world;
	body_ = body;
	body_->SetLeader(world_->agentLeader);
}

void Mind::update(const uint32_t dt) {
	body_->setTarget(world_->target());
}

void Mind::SearchNearbyAgents() {
	int agentsToFlee = 0;
	float meanX = 0;
	float meanY = 0;
	for (size_t i = 0; i < MAX_AGENTS; i++)
	{
		const MathLib::Vec2 directionAgentI = world_->ia(i)->getKinematic()->position;
		const MathLib::Vec2 directionActualAgent = body_->getKinematic()->position;

		float distance = directionAgentI.length() - directionActualAgent.length();
		//We check the others
		if (distance != 0) {

			if (distance < MAX_DISTANCE_COHESION) {
				agentsToFlee++;
				meanX += world_->ia(i)->getKinematic()->position.x();
				meanY += world_->ia(i)->getKinematic()->position.y();
			}
		}
	}
	if (meanX > 0 && meanY > 0) {
		meanX /= agentsToFlee;
		meanY /= agentsToFlee;
	}
	MathLib::Vec2 nuevaPos(meanX, meanY);
	AgentToFlee.position = nuevaPos;
	DebugDraw::drawCross(AgentToFlee.position, 0x00, 0x00, 0xFF, 0xFF);

	body_->setAgentToFlee(&AgentToFlee);
}

void Mind::CheckBoundaries() {


	/*
	if my pos is > radious + leader pos-> seek leader
	*/

	const MathLib::Vec2 directionAgentI = world_->agentLeader->getKinematic()->position;
	const MathLib::Vec2 directionActualAgent = body_->getKinematic()->position;

	float distance = (directionAgentI.length() + MAX_DISTANCE_SEPARATION) - directionActualAgent.length();
	//We check the others
	if (distance <= 0) {
		body_->setSteering(Body::SteeringMode::SeekLeader);
	}
}

