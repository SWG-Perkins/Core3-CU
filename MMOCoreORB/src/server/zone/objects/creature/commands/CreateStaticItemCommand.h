/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CREATESTATICITEMCOMMAND_H_
#define CREATESTATICITEMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CreateStaticItemCommand : public QueueCommand {
public:

	CreateStaticItemCommand(const String& name, ZoneProcessServer* server)
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

#endif //CREATESTATICITEMCOMMAND_H_
