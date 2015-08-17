/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef EVENTCLEARSTATESCOMMAND_H_
#define EVENTCLEARSTATESCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EventClearStatesCommand : public QueueCommand {
public:

	EventClearStatesCommand(const String& name, ZoneProcessServer* server)
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

#endif //EVENTCLEARSTATESCOMMAND_H_
