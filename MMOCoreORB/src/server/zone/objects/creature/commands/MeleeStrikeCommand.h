/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef MELEESTRIKECOMMAND_H_
#define MELEESTRIKECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "CombatQueueCommand.h"

class MeleeStrikeCommand : public CombatQueueCommand {
public:

	MeleeStrikeCommand(const String& name, ZoneProcessServer* server)
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

#endif //MELEESTRIKECOMMAND_H_
