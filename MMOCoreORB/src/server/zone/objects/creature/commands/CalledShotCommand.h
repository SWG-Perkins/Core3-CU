/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CALLEDSHOTCOMMAND_H_
#define CALLEDSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CalledShotCommand : public QueueCommand {
public:

	CalledShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //CALLEDSHOTCOMMAND_H_
