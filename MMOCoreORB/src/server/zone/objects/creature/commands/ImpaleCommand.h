/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef IMPALECOMMAND_H_
#define IMPALECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ImpaleCommand : public QueueCommand {
public:

	ImpaleCommand(const String& name, ZoneProcessServer* server)
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

#endif //IMPALECOMMAND_H_
