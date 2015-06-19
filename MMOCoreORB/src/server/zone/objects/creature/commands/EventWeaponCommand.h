/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef EVENTWEAPONCOMMAND_H_
#define EVENTWEAPONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EventWeaponCommand : public QueueCommand {
public:

	EventWeaponCommand(const String& name, ZoneProcessServer* server)
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

#endif //EVENTWEAPONCOMMAND_H_
