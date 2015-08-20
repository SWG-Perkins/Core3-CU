/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef ACTIVATEINSTANCECOMMAND_H_
#define ACTIVATEINSTANCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ActivateInstanceCommand : public QueueCommand {
public:

	ActivateInstanceCommand(const String& name, ZoneProcessServer* server)
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

#endif //ACTIVATEINSTANCECOMMAND_H_
