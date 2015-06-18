/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef ELECTROLITEDRAINCOMMAND_H_
#define ELECTROLITEDRAINCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ElectroliteDrainCommand : public QueueCommand {
public:

	ElectroliteDrainCommand(const String& name, ZoneProcessServer* server)
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

#endif //ELECTROLITEDRAINCOMMAND_H_
