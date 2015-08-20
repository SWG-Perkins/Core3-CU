/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SETTOUGHENCOMMAND_H_
#define SETTOUGHENCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetToughenCommand : public QueueCommand {
public:

	SetToughenCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETTOUGHENCOMMAND_H_
