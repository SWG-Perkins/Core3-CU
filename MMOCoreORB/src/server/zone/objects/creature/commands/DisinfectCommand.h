/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DISINFECTCOMMAND_H_
#define DISINFECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DisinfectCommand : public QueueCommand {
public:

	DisinfectCommand(const String& name, ZoneProcessServer* server)
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

#endif //DISINFECTCOMMAND_H_
