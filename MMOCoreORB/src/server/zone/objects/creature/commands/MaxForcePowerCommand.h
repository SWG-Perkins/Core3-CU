/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef MAXFORCEPOWERCOMMAND_H_
#define MAXFORCEPOWERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class MaxForcePowerCommand : public QueueCommand {
public:

	MaxForcePowerCommand(const String& name, ZoneProcessServer* server)
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

#endif //MAXFORCEPOWERCOMMAND_H_
