/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef QUICKDRAWCOMMAND_H_
#define QUICKDRAWCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class QuickDrawCommand : public CombatQueueCommand {
public:

	QuickDrawCommand(const String& name, ZoneProcessServer* server)
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

#endif //QUICKDRAWCOMMAND_H_
