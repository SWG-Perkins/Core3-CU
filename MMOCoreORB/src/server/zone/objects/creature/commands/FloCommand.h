/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FLOCOMMAND_H_
#define FLOCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class FloCommand : public QueueCommand {
public:

	FloCommand(const String& name, ZoneProcessServer* server)
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

#endif //FLOCOMMAND_H_
