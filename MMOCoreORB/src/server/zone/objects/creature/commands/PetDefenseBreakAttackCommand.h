/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PETDEFENSEBREAKATTACKCOMMAND_H_
#define DEADBANGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PetDefenseBreakAttackCommand : public QueueCommand {
public:

	PetDefenseBreakAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //PETDEFENSEBREAKATTACKCOMMAND_H_
