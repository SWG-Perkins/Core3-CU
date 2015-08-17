/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef RAMPAGECOMMAND_H_
#define RAMPAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RampageCommand : public QueueCommand {
public:

	RampageCommand(const String& name, ZoneProcessServer* server)
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

#endif //RAMPAGECOMMAND_H_
