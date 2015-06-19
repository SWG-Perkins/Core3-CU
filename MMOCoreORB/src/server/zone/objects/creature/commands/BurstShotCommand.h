/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef BURSTSHOTCOMMAND_H_
#define BURSTSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BurstShotCommand : public QueueCommand {
public:

	BurstShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //BURSTSHOTCOMMAND_H_
