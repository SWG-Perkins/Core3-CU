/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef COVERCOMMAND_H_
#define COVERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CoverCommand : public QueueCommand {
public:

	CoverCommand(const String& name, ZoneProcessServer* server)
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

#endif //COVERCOMMAND_H_
