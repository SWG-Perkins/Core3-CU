/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CREATUREBLINDATTACKCOMMAND_H_
#define CREATUREBLINDATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CreatureBlindAttackCommand : public QueueCommand {
public:

	CreatureBlindAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //CREATUREBLINDATTACKCOMMAND_H_
