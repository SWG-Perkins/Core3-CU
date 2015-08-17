/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CONCUSSIONSHOTCOMMAND_H_
#define CONCUSSIONSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ConcussionShotCommand : public QueueCommand {
public:

	ConcussionShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //CONCUSSIONSHOTCOMMAND_H_
