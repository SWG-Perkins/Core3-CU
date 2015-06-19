/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef BINDINGSTRIKECOMMAND_H_
#define BINDINGSTRIKECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BindingStrikeCommand : public QueueCommand {
public:

	BindingStrikeCommand(const String& name, ZoneProcessServer* server)
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

#endif //BINDINGSTRIKECOMMAND_H_
