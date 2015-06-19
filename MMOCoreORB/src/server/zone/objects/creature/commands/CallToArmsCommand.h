/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CALLTOARMSCOMMAND_H_
#define CALLTOARMSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CallToArmsCommand : public QueueCommand {
public:

	CallToArmsCommand(const String& name, ZoneProcessServer* server)
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

#endif //CALLTOARMSCOMMAND_H_
