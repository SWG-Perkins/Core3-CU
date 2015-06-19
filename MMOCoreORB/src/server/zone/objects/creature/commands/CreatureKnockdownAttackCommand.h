/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CREATUREKNOCKDOWNATTACKCOMMAND_H_
#define CREATUREKNOCKDOWNATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CreatureKnockdownAttackCommand : public QueueCommand {
public:

	CreatureKnockdownAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //CREATUREKNOCKDOWNATTACKCOMMAND_H_
