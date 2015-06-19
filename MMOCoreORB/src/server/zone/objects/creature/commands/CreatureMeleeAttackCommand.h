/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CREATUREMELEEATTACKCOMMAND_H_
#define CREATUREMELEEATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CreatureMeleeAttackCommand : public QueueCommand {
public:

	CreatureMeleeAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //CREATUREMELEEATTACKCOMMAND_H_
