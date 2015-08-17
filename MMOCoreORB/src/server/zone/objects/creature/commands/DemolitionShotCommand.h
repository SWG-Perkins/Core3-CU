/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DEMOLITIONSHOTCOMMAND_H_
#define DEMOLITIONSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DemolitionShotCommand : public QueueCommand {
public:

	DemolitionShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //DEMOLITIONSHOTCOMMAND_H_
