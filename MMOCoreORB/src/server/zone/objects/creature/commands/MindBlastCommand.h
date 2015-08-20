/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef MINDBLASTCOMMAND_H_
#define MINDBLASTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class MindBlastCommand : public QueueCommand {
public:

	MindBlastCommand(const String& name, ZoneProcessServer* server)
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

#endif //MINDBLASTCOMMAND_H_
