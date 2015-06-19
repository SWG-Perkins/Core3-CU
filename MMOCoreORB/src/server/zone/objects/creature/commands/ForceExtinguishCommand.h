/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEEXTINGUISHCOMMAND_H_
#define FORCEEXTINGUISHCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceExtinguishCommand : public QueueCommand {
public:

	ForceExtinguishCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCEEXTINGUISHCOMMAND_H_
