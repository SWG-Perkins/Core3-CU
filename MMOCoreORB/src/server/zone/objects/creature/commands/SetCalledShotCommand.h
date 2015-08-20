/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SETCALLEDSHOTCOMMAND_H_
#define SETCALLEDSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetCalledShotCommand : public QueueCommand {
public:

	SetCalledShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETCALLEDSHOTCOMMAND_H_
