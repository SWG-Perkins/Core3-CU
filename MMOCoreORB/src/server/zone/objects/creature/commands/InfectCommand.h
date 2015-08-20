/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef INFECTCOMMAND_H_
#define INFECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class InfectCommand : public QueueCommand {
public:

	InfectCommand(const String& name, ZoneProcessServer* server)
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

#endif //INFECTCOMMAND_H_
