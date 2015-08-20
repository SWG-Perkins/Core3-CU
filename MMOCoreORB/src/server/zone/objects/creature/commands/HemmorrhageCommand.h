/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef HEMMORRHAGECOMMAND_H_
#define HEMMORRHAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HemmorrhageCommand : public QueueCommand {
public:

	HemmorrhageCommand(const String& name, ZoneProcessServer* server)
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

#endif //HEMMORRHAGECOMMAND_H_
