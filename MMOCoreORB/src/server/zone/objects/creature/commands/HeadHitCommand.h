/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef HEADHITCOMMAND_H_
#define HEADHITCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HeadHitCommand : public QueueCommand {
public:

	HeadHitCommand(const String& name, ZoneProcessServer* server)
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

#endif //HEADHITCOMMAND_H_
