/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CREATURESTUNATTACKCOMMAND_H_
#define CREATURESTUNATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CreatureStunAttackCommand : public QueueCommand {
public:

	CreatureStunAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //CREATURESTUNATTACKCOMMAND_H_
