/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef EVENTDAMAGECOMMAND_H_
#define EVENTDAMAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EventDamageCommand : public QueueCommand {
public:

	EventDamageCommand(const String& name, ZoneProcessServer* server)
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

#endif //EVENTDAMAGECOMMAND_H_
