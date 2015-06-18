/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SETCALLTOARMSCOMMAND_H_
#define SETCALLTOARMSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetCallToArmsCommand : public QueueCommand {
public:

	SetCallToArmsCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETCALLTOARMSCOMMAND_H_
