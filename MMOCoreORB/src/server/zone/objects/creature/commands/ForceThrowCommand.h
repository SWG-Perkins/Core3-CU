/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCETHROWCOMMAND_H_
#define FORCETHROWCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceThrowCommand : public QueueCommand {
public:

	ForceThrowCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //FORCETHROWCOMMAND_H_
