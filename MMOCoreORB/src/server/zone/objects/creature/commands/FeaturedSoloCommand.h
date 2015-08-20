/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FEATUREDSOLOCOMMAND_H_
#define FEATUREDSOLOCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class FeaturedSoloCommand : public QueueCommand {
public:

	FeaturedSoloCommand(const String& name, ZoneProcessServer* server)
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

#endif //FEATUREDSOLOCOMMAND_H_
