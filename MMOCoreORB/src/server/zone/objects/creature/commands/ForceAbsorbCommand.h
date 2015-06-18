/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEABSORBCOMMAND_H_
#define FORCEABSORBCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceAbsorbCommand : public QueueCommand {
public:

	ForceAbsorbCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCEABSORBCOMMAND_H_
