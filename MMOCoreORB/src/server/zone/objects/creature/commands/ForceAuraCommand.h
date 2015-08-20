/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEAURACOMMAND_H_
#define FORCEAURACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceAuraCommand : public QueueCommand {
public:

	ForceAuraCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCEAURACOMMAND_H_
