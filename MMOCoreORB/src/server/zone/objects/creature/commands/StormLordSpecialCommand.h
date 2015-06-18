/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef STORMLORDSPECIALCOMMAND_H_
#define STORMLORDSPECIALCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class StormLordSpecialCommand : public QueueCommand {
public:

	StormLordSpecialCommand(const String& name, ZoneProcessServer* server)
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

#endif //STORMLORDSPECIALCOMMAND_H_
