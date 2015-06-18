/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CYBORGLIGHTNINGCOMMAND_H_
#define CYBORGLIGHTNINGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CyborgLightningCommand : public QueueCommand {
public:

	CyborgLightningCommand(const String& name, ZoneProcessServer* server)
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

#endif //CYBORGLIGHTNINGCOMMAND_H_
