/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef OVERKILLSHOTCOMMAND_H_
#define OVERKILLSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class OverkillShotCommand : public QueueCommand {
public:

	OverkillShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //OVERKILLSHOTCOMMAND_H_
