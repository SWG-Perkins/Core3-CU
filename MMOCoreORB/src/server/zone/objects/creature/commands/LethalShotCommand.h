/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef LETHALSHOTCOMMAND_H_
#define LETHALSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class LethalShotCommand : public CombatQueueCommand {
public:

	LethalShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //LETHALSHOTCOMMAND_H_
