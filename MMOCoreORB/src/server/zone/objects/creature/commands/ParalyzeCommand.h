/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef PARALYZECOMMAND_H_
#define PARALYZECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ParalyzeCommand : public QueueCommand {
public:

	ParalyzeCommand(const String& name, ZoneProcessServer* server)
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

#endif //PARALYZECOMMAND_H_
