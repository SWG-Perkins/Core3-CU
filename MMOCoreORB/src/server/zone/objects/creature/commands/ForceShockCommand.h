/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCESHOCKCOMMAND_H_
#define FORCESHOCKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceShockCommand : public QueueCommand {
public:

	ForceShockCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCESHOCKCOMMAND_H_
