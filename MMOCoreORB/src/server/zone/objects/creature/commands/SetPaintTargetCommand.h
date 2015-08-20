/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SETPAINTTARGETCOMMAND_H_
#define SETPAINTTARGETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetPaintTargetCommand : public QueueCommand {
public:

	SetPaintTargetCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETPAINTTARGETCOMMAND_H_
