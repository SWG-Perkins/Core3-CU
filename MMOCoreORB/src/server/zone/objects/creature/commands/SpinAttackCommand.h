/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SPINATTACKCOMMAND_H_
#define SPINATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SpinAttackCommand : public QueueCommand {
public:

	SpinAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //SPINATTACKCOMMAND_H_
