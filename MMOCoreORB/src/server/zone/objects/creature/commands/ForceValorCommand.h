/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEVALORCOMMAND_H_
#define FORCEVALORCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceValorCommand : public QueueCommand {
public:

	ForceValorCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCEVALORCOMMAND_H_
