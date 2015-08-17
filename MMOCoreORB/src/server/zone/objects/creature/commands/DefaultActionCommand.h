/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DEFAULTACTIONCOMMAND_H_
#define DEFAULTACTIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DefaultActionCommand : public QueueCommand {
public:

	DefaultActionCommand(const String& name, ZoneProcessServer* server)
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

#endif //DEFAULTACTIONCOMMAND_H_
