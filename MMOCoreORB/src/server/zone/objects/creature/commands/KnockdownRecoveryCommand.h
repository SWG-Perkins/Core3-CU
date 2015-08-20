/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef KNOCKDOWNRECOVERYCOMMAND_H_
#define KNOCKDOWNRECOVERYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class KnockdownRecoveryCommand : public QueueCommand {
public:

	KnockdownRecoveryCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isKnockedDown())
			return INVALIDSTATE;

		/*if (creature->isDizzied()) {
			if (System::random(100) > 25)
				creature->setPosture(CreaturePosture::UPRIGHT);
		} else*/
			creature->setPosture(CreaturePosture::UPRIGHT);

		//creature->removeEffect("state_knockeddown");

		return SUCCESS;
	}

};

#endif //KNOCKDOWNRECOVERYCOMMAND_H_
