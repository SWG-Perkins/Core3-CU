/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef GMWEAPONCOMMAND_H_
#define GMWEAPONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GmWeaponCommand : public QueueCommand {
public:

	GmWeaponCommand(const String& name, ZoneProcessServer* server)
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

#endif //GMWEAPONCOMMAND_H_
