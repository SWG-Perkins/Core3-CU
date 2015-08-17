/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FULLAUTOAREACOMMAND_H_
#define FULLAUTOAREACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class FullAutoAreaCommand : public QueueCommand {
public:

	FullAutoAreaCommand(const String& name, ZoneProcessServer* server)
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

#endif //FULLAUTOAREACOMMAND_H_
