/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef BLINDRECOVERYCOMMAND_H_
#define BLINDRECOVERYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BlindRecoveryCommand : public QueueCommand {
public:

	BlindRecoveryCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isKnockedDown())
			return INVALIDSTATE;



		//creature->removeEffect("state_blind");

		return SUCCESS;
	}

};

#endif //BLINDRECOVERYCOMMAND_H_
