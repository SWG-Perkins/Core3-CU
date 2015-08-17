/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEKNOCKDOWNCOMMAND_H_
#define FORCEKNOCKDOWNCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceKnockdownCommand : public QueueCommand {
public:

	ForceKnockdownCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCEKNOCKDOWNCOMMAND_H_
