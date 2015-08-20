/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef STARTLESHOTCOMMAND_H_
#define STARTLESHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class StartleShotCommand : public QueueCommand {
public:

	StartleShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //STARTLESHOTCOMMAND_H_
