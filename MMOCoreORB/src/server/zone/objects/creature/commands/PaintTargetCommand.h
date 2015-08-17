/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PAINTTARGETCOMMAND_H_
#define PAINTTARGETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PaintTargetCommand : public QueueCommand {
public:

	PaintTargetCommand(const String& name, ZoneProcessServer* server)
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

#endif //PAINTTARGETCOMMAND_H_
