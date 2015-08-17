/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef COUNTERTOXINSPRAYCOMMAND_H_
#define COUNTERTOXINSPRAYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CountertoxinSprayCommand : public QueueCommand {
public:

	CountertoxinSprayCommand(const String& name, ZoneProcessServer* server)
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

#endif //COUNTERTOXINSPRAYCOMMAND_H_
