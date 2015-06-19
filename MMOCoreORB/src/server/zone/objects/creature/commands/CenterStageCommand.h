/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CENTERSTAGECOMMAND_H_
#define CENTERSTAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CenterStageCommand : public QueueCommand {
public:

	CenterStageCommand(const String& name, ZoneProcessServer* server)
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

#endif //CENTERSTAGECOMMAND_H_
