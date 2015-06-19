/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef INSPIRECOMMAND_H_
#define INSPIRECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class InspireCommand : public QueueCommand {
public:

	InspireCommand(const String& name, ZoneProcessServer* server)
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

#endif //INSPIRECOMMAND_H_
