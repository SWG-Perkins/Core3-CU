/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PISTOLWHIPCOMMAND_H_
#define PISTOLWHIPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PistolWhipCommand : public QueueCommand {
public:

	PistolWhipCommand(const String& name, ZoneProcessServer* server)
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

#endif //PISTOLWHIPCOMMAND_H_
