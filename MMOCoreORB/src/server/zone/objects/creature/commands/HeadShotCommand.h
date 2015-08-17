/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef HEADSHOTCOMMAND_H_
#define HEADSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HeadShotCommand : public QueueCommand {
public:

	HeadShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //HEADSHOTCOMMAND_H_
