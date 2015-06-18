/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PETINTIMIDATEATTACKCOMMAND_H_
#define PETINTIMIDATEATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PetIntimidateAttackCommand : public QueueCommand {
public:

	PetIntimidateAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //PETINTIMIDATEATTACKCOMMAND_H_
