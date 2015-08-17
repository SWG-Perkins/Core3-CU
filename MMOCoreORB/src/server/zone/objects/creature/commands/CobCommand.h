/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef COBCOMMAND_H_
#define COBCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CobCommand : public QueueCommand {
public:

	CobCommand(const String& name, ZoneProcessServer* server)
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

#endif //COBCOMMAND_H_
