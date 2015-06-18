/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEWOUNDHEALCOMMAND_H_
#define FORCEWOUNDHEALCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceWoundHealCommand : public QueueCommand {
public:

	ForceWoundHealCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCEWOUNDHEALCOMMAND_H_
