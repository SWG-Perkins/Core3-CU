/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef RESPECSTATCOMMITCOMMAND_H_
#define RESPECSTATCOMMITCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RespecStatCommitCommand : public QueueCommand {
public:

	RespecStatCommitCommand(const String& name, ZoneProcessServer* server)
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

#endif //REPECSTATCOMMITCOMMAND_H_
