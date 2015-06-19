/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DOUBLETIMECOMMAND_H_
#define DOUBLETIMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DoubleTimeCommand : public QueueCommand {
public:

	DoubleTimeCommand(const String& name, ZoneProcessServer* server)
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

#endif //DOUBLETIMECOMMAND_H_
