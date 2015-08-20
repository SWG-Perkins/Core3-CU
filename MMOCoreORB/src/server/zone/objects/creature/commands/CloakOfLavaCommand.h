/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CLOAKOFLAVACOMMAND_H_
#define CLOAKOFLAVACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CloakOfLavaCommand : public QueueCommand {
public:

	CloakOfLavaCommand(const String& name, ZoneProcessServer* server)
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

#endif //CLOAKOFLAVACOMMAND_H_
