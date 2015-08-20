/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef THROWTHERMAL_DETONATORGRENADECOMMAND_H_
#define THROWTHERMAL_DETONATORGRENADECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class Throwthermal_detonatorGrenadeCommand : public QueueCommand {
public:

	Throwthermal_detonatorGrenadeCommand(const String& name, ZoneProcessServer* server)
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

#endif //THROWTHERMAL_DETONATORGRENADECOMMAND_H_
