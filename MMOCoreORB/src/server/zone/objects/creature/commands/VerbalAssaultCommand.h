/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef VERBALASSAULTCOMMAND_H_
#define VERBALASSAULTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class VerbalAssaultCommand : public QueueCommand {
public:

	VerbalAssaultCommand(const String& name, ZoneProcessServer* server)
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

#endif //VERBALASSAULTCOMMAND_H_
