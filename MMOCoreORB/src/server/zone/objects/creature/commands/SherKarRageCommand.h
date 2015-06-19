/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SHERKARRAGECOMMAND_H_
#define SHERKARRAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SherKarRageCommand : public QueueCommand {
public:

	SherKarRageCommand(const String& name, ZoneProcessServer* server)
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

#endif //SHERKARRAGECOMMAND_H_
