/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef WARCRYCOMMAND_H_
#define WARCRYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class WarcryCommand : public QueueCommand {
public:

	WarcryCommand(const String& name, ZoneProcessServer* server)
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

#endif //WARCRYCOMMAND_H_
