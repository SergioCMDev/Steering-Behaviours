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
		float distance = world_->ia(i)->getKinematic()->position.length() - this->body_->getKinematic.getKinematic()->position.lentgh();
		//We check the others
		if (distance  != 0) {

			if (world_->ia(i)->getKinematic()->position.length() < this->body_->getKinematic.getKinematic()->position.lentgh() +  MAX_DISTANCE_COHESION) {
				//iaToFlee[i] = world_->ia(i);
				agentsToFlee++;
				meanX += world_->ia(i)->getKinematic()->position.X;
				meanY += world_->ia(i)->getKinematic()->position.Y;
			}
		}
	}
	meanX /= agentsToFlee;
	meanY /= agentsToFlee;
	//AgentToFlee->position.x = meanX;
	//AgentToFlee->position.y = meanY;
	//body_->setAgentToFlee(AgentToFlee);
}
