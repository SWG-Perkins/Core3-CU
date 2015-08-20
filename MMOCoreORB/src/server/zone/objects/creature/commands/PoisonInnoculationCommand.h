/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef POISONINNOCULATIONCOMMAND_H_
#define POISONINNOCULATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PoisonInnoculationCommand : public QueueCommand {
public:

	PoisonInnoculationCommand(const String& name, ZoneProcessServer* server)
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

#endif //POISONINNOCULATIONCOMMAND_H_
