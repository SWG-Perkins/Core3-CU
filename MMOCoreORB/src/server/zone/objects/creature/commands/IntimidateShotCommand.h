/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef INTIMIDATESHOTCOMMAND_H_
#define INTIMIDATESHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class IntimidateShotCommand : public QueueCommand {
public:

	IntimidateShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //INTIMIDATESHOTCOMMAND_H_
