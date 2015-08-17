/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef EVENTSTOREPETCOMMAND_H_
#define EVENTSTOREPETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EventStorePetCommand : public QueueCommand {
public:

	EventStorePetCommand(const String& name, ZoneProcessServer* server)
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

#endif //EVENTSTOREPETCOMMAND_H_
