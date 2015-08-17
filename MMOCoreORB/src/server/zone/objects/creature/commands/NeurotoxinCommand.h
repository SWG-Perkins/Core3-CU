/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef NEUROTOXINCOMMAND_H_
#define NEUROTOXINCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class NeurotoxinCommand : public QueueCommand {
public:

	NeurotoxinCommand(const String& name, ZoneProcessServer* server)
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

#endif //NEUROTOXINCOMMAND_H_
