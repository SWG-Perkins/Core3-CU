/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PARRYRIPOSTECOMMAND_H_
#define PARRYRIPOSTECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ParryRiposteCommand : public QueueCommand {
public:

	ParryRiposteCommand(const String& name, ZoneProcessServer* server)
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

#endif //PARRYRIPOSTECOMMAND_H_
