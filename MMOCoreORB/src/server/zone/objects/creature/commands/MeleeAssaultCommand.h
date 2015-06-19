/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef MELEEASSAULTCOMMAND_H_
#define MELEEASSAULTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class MeleeAssaultCommand : public QueueCommand {
public:

	MeleeAssaultCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //MELEEASSAULTCOMMAND_H_
