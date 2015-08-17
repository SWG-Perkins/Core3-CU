/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DIZZYRECOVERYCOMMAND_H_
#define DIZZYRECOVERYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DizzyRecoveryCommand : public QueueCommand {
public:

	DizzyRecoveryCommand(const String& name, ZoneProcessServer* server)
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

#endif //DIZZYRECOVERYCOMMAND_H_
