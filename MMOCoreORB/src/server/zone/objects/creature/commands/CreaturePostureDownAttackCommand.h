/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CREATUREPOSTUREDOWNATTACKCOMMAND_H_
#define CREATUREPOSTUREDOWNATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CreaturePostureDownAttackCommand : public QueueCommand {
public:

	CreaturePostureDownAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //CREATUREPOSTUREDOWNATTACKCOMMAND_H_
