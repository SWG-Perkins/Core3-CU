/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef BACTASPRAYCOMMAND_H_
#define BACTASPRAYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BactaSprayCommand : public QueueCommand {
public:

	BactaSprayCommand(const String& name, ZoneProcessServer* server)
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

#endif //BACTASPRAYCOMMAND_H_
