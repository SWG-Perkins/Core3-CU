/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef EVENTBUFFTARGETCOMMAND_H_
#define EVENTBUFFTARGETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EventBuffTargetCommand : public QueueCommand {
public:

	EventBuffTargetCommand(const String& name, ZoneProcessServer* server)
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

#endif //EVENTBUFFTARGETCOMMAND_H_
