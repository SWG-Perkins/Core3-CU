/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef LEGSWEEPCOMMAND_H_
#define LEGSWEEPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class LegSweepCommand : public QueueCommand {
public:

	LegSweepCommand(const String& name, ZoneProcessServer* server)
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

#endif //LEGSWEEPCOMMAND_H_
