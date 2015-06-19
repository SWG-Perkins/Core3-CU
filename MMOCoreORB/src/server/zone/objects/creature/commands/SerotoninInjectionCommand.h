/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SEROTONININJECTIONCOMMAND_H_
#define SEROTONININJECTIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SerotoninInjectionCommand : public QueueCommand {
public:

	SerotoninInjectionCommand(const String& name, ZoneProcessServer* server)
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

#endif //SEROTONININJECTIONCOMMAND_H_
