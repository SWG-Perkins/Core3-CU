/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEARMORCOMMAND_H_
#define FORCEARMORCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceArmorCommand : public QueueCommand {
public:

	ForceArmorCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCEARMORCOMMAND_H_
