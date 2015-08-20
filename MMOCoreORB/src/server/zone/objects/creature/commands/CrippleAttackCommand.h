/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CRIPPLEATTACKCOMMAND_H_
#define CRIPPLEATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CrippleAttackCommand : public QueueCommand {
public:

	CrippleAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //CRIPPLEATTACKCOMMAND_H_
