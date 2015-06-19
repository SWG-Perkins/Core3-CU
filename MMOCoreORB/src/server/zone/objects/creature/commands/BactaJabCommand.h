/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef BACTAJABCOMMAND_H_
#define BACTAJABCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BactaJabCommand : public QueueCommand {
public:

	BactaJabCommand(const String& name, ZoneProcessServer* server)
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

#endif //BACTAJABCOMMAND_H_
