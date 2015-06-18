/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef NUTRIENTINJECTIONCOMMAND_H_
#define NUTRIENTINJECTIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class NutrientInjectionCommand : public QueueCommand {
public:

	NutrientInjectionCommand(const String& name, ZoneProcessServer* server)
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

#endif //NUTRIENTINJECTIONCOMMAND_H_
