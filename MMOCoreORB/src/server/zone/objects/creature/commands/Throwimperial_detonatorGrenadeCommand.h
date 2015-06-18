/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef THROWIMPERIAL_DETONATORGRENADECOMMAND_H_
#define THROWIMPERIAL_DETONATORGRENADECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class Throwimperial_detonatorGrenadeCommand : public QueueCommand {
public:

	Throwimperial_detonatorGrenadeCommand(const String& name, ZoneProcessServer* server)
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

#endif //THROWIMPERIAL_DETONATORGRENADECOMMAND_H_
