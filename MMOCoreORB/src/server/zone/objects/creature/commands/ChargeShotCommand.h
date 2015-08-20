/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CHARGESHOTCOMMAND_H_
#define CHARGESHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ChargeShotCommand : public CombatQueueCommand {
public:

	ChargeShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return doCombatAction(creature, target);
	}

};

#endif //CHARGESHOTCOMMAND_H_
