/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PLACEDSHOTCOMMAND_H_
#define PLACEDSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PlacedShotCommand : public CombatQueueCommand {
public:

	PlacedShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //PLACEDSHOTCOMMAND_H_
