/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef RANGEDSHOTCOMMAND_H_
#define RANGEDSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RangedShotCommand : public CombatQueueCommand {
public:

	RangedShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //RANGEDSHOTCOMMAND_H_
