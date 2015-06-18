/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SCATTERHITCOMMAND_H_
#define SCATTERHITCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ScatterHitCommand : public QueueCommand {
public:

	ScatterHitCommand(const String& name, ZoneProcessServer* server)
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

#endif //SCATTERHITCOMMAND_H_
