/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCESTRIKECOMMAND_H_
#define FORCESTRIKECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceStrikeCommand : public QueueCommand {
public:

	ForceStrikeCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCESTRIKECOMMAND_H_
