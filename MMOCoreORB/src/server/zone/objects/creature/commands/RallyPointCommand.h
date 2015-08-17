/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef RALLYPOINTCOMMAND_H_
#define RALLYPOINTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RallyPointCommand : public QueueCommand {
public:

	RallyPointCommand(const String& name, ZoneProcessServer* server)
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

#endif //RALLYPOINTCOMMAND_H_
