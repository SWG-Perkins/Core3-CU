/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PETSTUNATTACKCOMMAND_H_
#define PETSTUNATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PetStunAttackCommand : public QueueCommand {
public:

	PetStunAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //PETSTUNATTACKCOMMAND_H_
