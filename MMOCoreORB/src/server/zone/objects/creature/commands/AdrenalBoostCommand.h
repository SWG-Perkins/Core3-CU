/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef ADRENALBOOSTCOMMAND_H_
#define ADRENALBOOSTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AdrenalBoostCommand : public QueueCommand {
public:

	AdrenalBoostCommand(const String& name, ZoneProcessServer* server)
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

#endif //ADRENALBOOSTCOMMAND_H_
