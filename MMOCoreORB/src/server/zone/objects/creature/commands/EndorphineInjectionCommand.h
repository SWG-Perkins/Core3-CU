/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef ENDORPHINEINJECTIONCOMMAND_H_
#define ENDORPHINEINJECTIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EndorphineInjectionCommand : public QueueCommand {
public:

	EndorphineInjectionCommand(const String& name, ZoneProcessServer* server)
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

#endif //ENDORPHINEINJECTIONCOMMAND_H_
