/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef POINTBLANKAREACOMMAND_H_
#define POINTBLANKAREACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PointBlankAreaCommand : public QueueCommand {
public:

	PointBlankAreaCommand(const String& name, ZoneProcessServer* server)
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

#endif //POINTBLANKAREACOMMAND_H_
