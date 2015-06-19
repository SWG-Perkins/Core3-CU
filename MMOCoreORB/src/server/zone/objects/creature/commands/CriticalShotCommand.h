/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CRITICALSHOTCOMMAND_H_
#define CRITICALSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CriticalShotCommand : public QueueCommand {
public:

	CriticalShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //CRITICALSHOTCOMMAND_H_
