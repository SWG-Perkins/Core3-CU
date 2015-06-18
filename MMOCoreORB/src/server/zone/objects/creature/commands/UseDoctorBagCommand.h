/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef USEDOCTORBAGCOMMAND_H_
#define USEDOCTORBAGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class UseDoctorBagCommand : public QueueCommand {
public:

	UseDoctorBagCommand(const String& name, ZoneProcessServer* server)
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

#endif //USEDOCTORBAGCOMMAND_H_
