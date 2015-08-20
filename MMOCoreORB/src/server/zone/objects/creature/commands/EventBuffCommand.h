/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef EVENTBUFFCOMMAND_H_
#define EVENTBUFFCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EventBuffCommand : public QueueCommand {
public:

	EventBuffCommand(const String& name, ZoneProcessServer* server)
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

#endif //EVENTBUFFCOMMAND_H_
