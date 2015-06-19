/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SETTACTICSCOMMAND_H_
#define SETTACTICSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetTacticsCommand : public QueueCommand {
public:

	SetTacticsCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETTACTICSCOMMAND_H_
