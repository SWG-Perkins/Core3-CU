/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SHOCKCOMMAND_H_
#define SHOCKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ShockCommand : public QueueCommand {
public:

	ShockCommand(const String& name, ZoneProcessServer* server)
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

#endif //SHOCKCOMMAND_H_
