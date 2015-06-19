/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef EUPHORIACOMMAND_H_
#define EUPHORIACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EuphoriaCommand : public QueueCommand {
public:

	EuphoriaCommand(const String& name, ZoneProcessServer* server)
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

#endif //EUPHORIACOMMAND_H_
