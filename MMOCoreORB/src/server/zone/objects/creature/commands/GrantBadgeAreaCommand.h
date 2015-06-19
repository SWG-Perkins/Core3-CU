/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef GRANTBADGEAREACOMMAND_H_
#define GRANTBADGEAREACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GrantBadgeAreaCommand : public QueueCommand {
public:

	GrantBadgeAreaCommand(const String& name, ZoneProcessServer* server)
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

#endif //GRANTBADGEAREACOMMAND_H_
