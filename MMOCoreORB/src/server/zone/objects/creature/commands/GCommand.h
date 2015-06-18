/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef GCOMMAND_H_
#define GGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GCommand : public QueueCommand {
public:

	GCommand(const String& name, ZoneProcessServer* server)
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

#endif //GCOMMAND_H_
