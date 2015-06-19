/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef ABANDONQUESTCOMMAND_H_
#define ABANDONQUESTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AbandonQuestCommand : public QueueCommand {
public:

	AbandonQuestCommand(const String& name, ZoneProcessServer* server)
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

#endif //ABANDONQUESTCOMMAND_H_
