/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SETDOUBLETIMECOMMAND_H_
#define SETDOUBLETIMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetDoubleTimeCommand : public QueueCommand {
public:

	SetDoubleTimeCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETDOUBLETIMECOMMAND_H_
