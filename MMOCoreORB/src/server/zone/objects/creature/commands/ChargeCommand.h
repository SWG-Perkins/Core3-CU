/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CHARGECOMMAND_H_
#define CHARGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ChargeCommand : public QueueCommand {
public:

	ChargeCommand(const String& name, ZoneProcessServer* server)
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

#endif //CHARGECOMMAND_H_
