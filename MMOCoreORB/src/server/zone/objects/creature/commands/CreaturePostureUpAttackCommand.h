/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CREATUREPOSTUREUPATTACKCOMMAND_H_
#define CREATUREPOSTUREUPATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CreaturePostureUpAttackCommand : public QueueCommand {
public:

	CreaturePostureUpAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //CREATUREPOSTUREUPATTACKCOMMAND_H_
