/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DECONTAMINATECOMMAND_H_
#define DECONTAMINATECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DecontaminateCommand : public QueueCommand {
public:

	DecontaminateCommand(const String& name, ZoneProcessServer* server)
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

#endif //DECONTAMINATECOMMAND_H_
