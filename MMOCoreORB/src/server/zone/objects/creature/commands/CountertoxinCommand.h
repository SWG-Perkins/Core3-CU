/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef COUNTERTOXINCOMMAND_H_
#define COUNTERTOXINCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CountertoxinCommand : public QueueCommand {
public:

	CountertoxinCommand(const String& name, ZoneProcessServer* server)
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

#endif //COUNTERTOXINCOMMAND_H_
