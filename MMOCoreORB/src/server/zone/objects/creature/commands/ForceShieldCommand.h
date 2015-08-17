/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCESHIELDCOMMAND_H_
#define FORCESHIELDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceShieldCommand : public QueueCommand {
public:

	ForceShieldCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCESHIELDOMMAND_H_
