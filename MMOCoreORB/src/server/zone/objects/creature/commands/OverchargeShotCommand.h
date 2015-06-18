/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef OVERCHARGESHOTCOMMAND_H_
#define OVERCHARGESHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class OverchargeShotCommand : public CombatQueueCommand {
public:

	OverchargeShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return doCombatAction(creature, target);
	}

};

#endif //OVERCHARGESHOTCOMMAND_H_
