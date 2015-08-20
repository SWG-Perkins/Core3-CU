/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CYBORGSURESHOTCOMMAND_H_
#define CYBORGSURESHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CyborgSureShotCommand : public QueueCommand {
public:

	CyborgSureShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //CYBORGSURESHOTCOMMAND_H_
