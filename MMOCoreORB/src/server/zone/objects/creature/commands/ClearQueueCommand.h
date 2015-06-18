/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CLEARQUEUECOMMAND_H_
#define CLEARQUEUECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ClearQueueCommand : public QueueCommand {
public:

	ClearQueueCommand(const String& name, ZoneProcessServer* server)
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

#endif //CLEARQUEUECOMMAND_H_
