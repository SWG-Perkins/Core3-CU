/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FLOORLIGHTSCOMMAND_H_
#define FLOORLIGHTSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class FloorLightsCommand : public QueueCommand {
public:

	FloorLightsCommand(const String& name, ZoneProcessServer* server)
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

#endif //FLOORLIGHTSCOMMAND_H_
