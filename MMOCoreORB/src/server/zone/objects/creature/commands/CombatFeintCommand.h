/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef COMBATFEINTCOMMAND_H_
#define COMBATFEINTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CombatFeintCommand : public QueueCommand {
public:

	CombatFeintCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //COMBATFEINTCOMMAND_H_
