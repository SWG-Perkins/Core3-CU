/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef EVENTMOVETOMECOMMAND_H_
#define EVENTMOVETOMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EventMoveToMeCommand : public QueueCommand {
public:

	EventMoveToMeCommand(const String& name, ZoneProcessServer* server)
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

#endif //EVENTMOVETOMECOMMAND_H_
