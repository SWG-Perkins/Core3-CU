/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PETBLEEDATTACKCOMMAND_H_
#define PETBLEEDATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PetBleedAttackCommand : public QueueCommand {
public:

	PetBleedAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //PETBLEEDATTACKCOMMAND_H_
