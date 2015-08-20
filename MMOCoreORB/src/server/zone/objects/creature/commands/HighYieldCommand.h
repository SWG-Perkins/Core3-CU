/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef HIGHYIELDCOMMAND_H_
#define HIGHYIELDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HighYieldCommand : public QueueCommand {
public:

	HighYieldCommand(const String& name, ZoneProcessServer* server)
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

#endif //HIGHYIELDCOMMAND_H_
