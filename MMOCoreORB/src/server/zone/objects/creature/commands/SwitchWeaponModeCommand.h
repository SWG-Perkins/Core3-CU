/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SWITCHWEAPONMODECOMMAND_H_
#define SWITCHWEAPONMODECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SwitchWeaponModeCommand : public QueueCommand {
public:

	SwitchWeaponModeCommand(const String& name, ZoneProcessServer* server)
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

#endif //SWITCHWEAPONMODECOMMANDCOMMAND_H_
