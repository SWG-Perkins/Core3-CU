/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef BACTATOSSCOMMAND_H_
#define BACTATOSSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BactaTossCommand : public QueueCommand {
public:

	BactaTossCommand(const String& name, ZoneProcessServer* server)
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

#endif //BACTATOSSCOMMAND_H_
