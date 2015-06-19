/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef THROWBUGGRENADECOMMAND_H_
#define THROWBUGGRENADECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ThrowbugGrenadeCommand : public QueueCommand {
public:

	ThrowbugGrenadeCommand(const String& name, ZoneProcessServer* server)
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

#endif //THROWBUGGRENADECOMMAND_H_
