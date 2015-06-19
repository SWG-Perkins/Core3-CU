/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DISARMINGSHOTCOMMAND_H_
#define DISARMINGSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DisarmingShotCommand : public QueueCommand {
public:

	DisarmingShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //DISARMINGSHOTCOMMAND_H_
