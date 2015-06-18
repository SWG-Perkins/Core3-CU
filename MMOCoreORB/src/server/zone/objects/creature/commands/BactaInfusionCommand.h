/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef BACTAINFUSIONCOMMAND_H_
#define BACTAINFUSIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BactaInfusionCommand : public QueueCommand {
public:

	BactaInfusionCommand(const String& name, ZoneProcessServer* server)
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

#endif //BACTAINFUSIONCOMMAND_H_
