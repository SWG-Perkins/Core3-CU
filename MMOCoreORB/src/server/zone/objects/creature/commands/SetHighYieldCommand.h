/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SETHIGHYIELDCOMMAND_H_
#define SETHIGHYIELDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetHighYieldCommand : public QueueCommand {
public:

	SetHighYieldCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETHIGHYIELDCOMMAND_H_
