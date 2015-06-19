/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERTHROWCOMMAND_H_
#define SABERTHROWCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberThrowCommand : public CombatQueueCommand {
public:

	SaberThrowCommand(const String& name, ZoneProcessServer* server)
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

#endif //SABERTHROWCOMMAND_H_
