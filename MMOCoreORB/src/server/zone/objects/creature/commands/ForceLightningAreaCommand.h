/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCELIGHTNINGAREACOMMAND_H_
#define FORCELIGHTNINGAREACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"

class ForceLightningAreaCommand : public ForcePowersQueueCommand {
public:

	ForceLightningAreaCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCELIGHTNINGAREACOMMAND_H_
