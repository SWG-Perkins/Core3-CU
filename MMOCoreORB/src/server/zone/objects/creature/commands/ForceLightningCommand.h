/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCELIGHTNINGCOMMAND_H_
#define FORCELIGHTNINGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "ForcePowersQueueCommand.h"

class ForceLightningCommand : public ForcePowersQueueCommand {
public:

	ForceLightningCommand(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return doCombatAction(creature, target);
	}

};

#endif //FORCELIGHTNINGCOMMAND_H_
