/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PETSNAREATTACKCOMMAND_H_
#define PETSNAREATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PetSnareAttackCommand : public QueueCommand {
public:

	PetSnareAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //PETSNAREATTACKCOMMAND_H_
