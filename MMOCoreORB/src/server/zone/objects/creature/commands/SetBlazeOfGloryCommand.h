/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SETBLAZEOFGLORYCOMMAND_H_
#define SETBLAZEOFGLORYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetBlazeOfGloryCommand : public QueueCommand {
public:

	SetBlazeOfGloryCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETBLAZEOFGLORYCOMMAND_H_
