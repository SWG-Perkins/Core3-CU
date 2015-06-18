/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PETBLINDATTACKCOMMAND_H_
#define PETBLINDATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PetBlindAttackCommand : public QueueCommand {
public:

	PetBlindAttackCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //PETBLINDATTACKCOMMAND_H_
