/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef THROWPROTONGRENADECOMMAND_H_
#define THROWPROTONGRENADECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ThrowprotonGrenadeCommand : public QueueCommand {
public:

	ThrowprotonGrenadeCommand(const String& name, ZoneProcessServer* server)
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

#endif //THROWPROTONGRENADECOMMAND_H_
