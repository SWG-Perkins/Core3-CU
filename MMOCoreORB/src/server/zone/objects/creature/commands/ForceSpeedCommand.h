/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCESPEEDCOMMAND_H_
#define FORCESPEEDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceSpeedCommand : public QueueCommand {
public:

	ForceSpeedCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCESPEEDCOMMAND_H_
