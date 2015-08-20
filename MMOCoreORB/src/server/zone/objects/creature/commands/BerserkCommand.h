/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef BERSERKCOMMAND_H_
#define BERSERKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BerserkCommand : public QueueCommand {
public:

	BerserkCommand(const String& name, ZoneProcessServer* server)
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

#endif //BERSERKCOMMAND_H_
