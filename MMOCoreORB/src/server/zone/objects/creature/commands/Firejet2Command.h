/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FIREJET2COMMAND_H_
#define FIREJET2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class Firejet2Command : public QueueCommand {
public:

	Firejet2Command(const String& name, ZoneProcessServer* server)
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

#endif //FIREJET2COMMAND_H_
