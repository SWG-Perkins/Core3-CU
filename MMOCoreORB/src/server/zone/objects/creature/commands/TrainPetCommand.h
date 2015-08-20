/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef TRAINPETCOMMAND_H_
#define TRAINPETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class TrainPetCommand : public QueueCommand {
public:

	TrainPetCommand(const String& name, ZoneProcessServer* server)
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

#endif //TRAINPETCOMMAND_H_
