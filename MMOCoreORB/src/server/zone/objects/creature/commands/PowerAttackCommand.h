/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef POWERATTACKCOMMAND_H_
#define POWERATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PowerAttackCommand : public QueueCommand {
public:

	PowerAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //POWERATTACKCOMMAND_H_
