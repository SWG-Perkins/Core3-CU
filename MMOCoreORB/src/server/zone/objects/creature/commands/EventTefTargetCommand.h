/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef EVENTTEFTARGETCOMMAND_H_
#define EVENTTEFTARGETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EventTefTargetCommand : public QueueCommand {
public:

	EventTefTargetCommand(const String& name, ZoneProcessServer* server)
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

#endif //EVENTTEFTARGETCOMMAND_H_
