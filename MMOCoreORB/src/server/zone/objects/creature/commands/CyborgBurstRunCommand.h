/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CYBORGBURSTRUNCOMMAND_H_
#define CYBORGBURSTRUNCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CyborgBurstRunCommand : public QueueCommand {
public:

	CyborgBurstRunCommand(const String& name, ZoneProcessServer* server)
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

#endif //CYBORGBURSTRUNCOMMAND_H_
