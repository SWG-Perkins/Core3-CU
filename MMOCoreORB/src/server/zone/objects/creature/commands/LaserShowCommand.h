/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef LASERSHOWCOMMAND_H_
#define LASERSHOWCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class LaserShowCommand : public QueueCommand {
public:

	LaserShowCommand(const String& name, ZoneProcessServer* server)
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

#endif //LASERSHOWCOMMAND_H_
