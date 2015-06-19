/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef BODYHITCOMMAND_H_
#define BODYHITCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BodyHitCommand : public QueueCommand {
public:

	BodyHitCommand(const String& name, ZoneProcessServer* server)
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

#endif //BODYHITCOMMAND_H_
