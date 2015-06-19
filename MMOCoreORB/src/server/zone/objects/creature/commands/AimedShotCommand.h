/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef AIMEDSHOTCOMMAND_H_
#define AIMEDSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AimedShotCommand : public CombatQueueCommand {
public:

	AimedShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //AIMEDSHOTCOMMAND_H_
