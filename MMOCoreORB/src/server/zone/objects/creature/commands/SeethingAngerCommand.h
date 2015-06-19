/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SEETHINGANGERCOMMAND_H_
#define SEETHINGANGERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SeethingAngerCommand : public QueueCommand {
public:

	SeethingAngerCommand(const String& name, ZoneProcessServer* server)
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

#endif //SEETHINGANGERCOMMAND_H_
