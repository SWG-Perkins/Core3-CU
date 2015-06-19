/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef TACTICSCOMMAND_H_
#define TACTICSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class TacticsCommand : public QueueCommand {
public:

	TacticsCommand(const String& name, ZoneProcessServer* server)
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

#endif //TACTICSCOMMAND_H_
