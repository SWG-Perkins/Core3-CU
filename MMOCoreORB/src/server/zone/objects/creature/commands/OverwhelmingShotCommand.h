/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef OVERWHELMINGSHOTCOMMAND_H_
#define OVERWHELMINGSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class OverwhelmingShotCommand : public QueueCommand {
public:

	OverwhelmingShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //OVERWHELMINGSHOTCOMMAND_H_
