/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SECONDCHANCECOMMAND_H_
#define SECONDCHANCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SecondChanceCommand : public QueueCommand {
public:

	SecondChanceCommand(const String& name, ZoneProcessServer* server)
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

#endif //SECONDCHANCECOMMAND_H_
