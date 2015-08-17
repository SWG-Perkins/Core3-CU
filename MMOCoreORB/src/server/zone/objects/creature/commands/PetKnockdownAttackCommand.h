/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PETKNOCKDOWNATTACKCOMMAND_H_
#define PETKNOCKDOWNATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PetKnockdownAttackCommand : public QueueCommand {
public:

	PetKnockdownAttackCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //PETKNOCKDOWNATTACKCOMMAND_H_
