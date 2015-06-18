/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef THROWFRAGMENTATIONGRENADECOMMAND_H_
#define THROWFRAGMENTATIONGRNADEGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ThrowfragmentationGrenadeCommand : public QueueCommand {
public:

	ThrowfragmentationGrenadeCommand(const String& name, ZoneProcessServer* server)
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

#endif //THROWFRAGMENTATIONGRENADECOMMAND_H_
