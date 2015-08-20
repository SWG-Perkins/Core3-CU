/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef ARMORBREAKCOMMAND_H_
#define ARMORBREAKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ArmorBreakCommand : public QueueCommand {
public:

	ArmorBreakCommand(const String& name, ZoneProcessServer* server)
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

#endif //ARMORBREAKCOMMAND_H_
