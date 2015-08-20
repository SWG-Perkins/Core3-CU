/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef STUNRECOVERYCOMMAND_H_
#define STUNRECOVERYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class StunRecoveryCommand : public QueueCommand {
public:

	StunRecoveryCommand(const String& name, ZoneProcessServer* server)
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

#endif //STUNRECOVERYCOMMAND_H_
