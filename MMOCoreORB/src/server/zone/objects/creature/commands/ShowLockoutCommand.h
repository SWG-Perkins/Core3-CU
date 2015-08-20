/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SHOWLOCKOUTCOMMAND_H_
#define SHOWLOCKOUTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ShowLockoutCommand : public QueueCommand {
public:

	ShowLockoutCommand(const String& name, ZoneProcessServer* server)
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

#endif //SHOWLOCKOUTCOMMAND_H_
