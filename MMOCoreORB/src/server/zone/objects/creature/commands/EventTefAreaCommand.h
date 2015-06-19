/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef EVENTTEFAREACOMMAND_H_
#define EVENTTEFAREACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EventTefAreaCommand : public QueueCommand {
public:

	EventTefAreaCommand(const String& name, ZoneProcessServer* server)
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

#endif //EVENTTEFAREACOMMAND_H_
