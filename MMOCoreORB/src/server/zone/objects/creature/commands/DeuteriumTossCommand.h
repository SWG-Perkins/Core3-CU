/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DEUTERIUMTOSSCOMMAND_H_
#define DEUTERIUMTOSSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DeuteriumTossCommand : public QueueCommand {
public:

	DeuteriumTossCommand(const String& name, ZoneProcessServer* server)
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

#endif //DEUTERIUMTOSSCOMMAND_H_
