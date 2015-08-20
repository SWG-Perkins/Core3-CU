/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef THYROIDRUPTURECOMMAND_H_
#define THYROIDRUPTURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ThyroidRuptureCommand : public QueueCommand {
public:

	ThyroidRuptureCommand(const String& name, ZoneProcessServer* server)
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

#endif //THYROIDRUPTURECOMMAND_H_
