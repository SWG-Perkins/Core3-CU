/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SWEEPATTACKCOMMAND_H_
#define SWEEPATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SweepAttackCommand : public QueueCommand {
public:

	SweepAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //SWEEPATTACKCOMMAND_H_
