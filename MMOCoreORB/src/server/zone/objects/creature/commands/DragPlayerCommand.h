/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DRAGPLAYERCOMMAND_H_
#define DRAGPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DragPlayerCommand : public QueueCommand {
public:

	DragPlayerCommand(const String& name, ZoneProcessServer* server)
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

#endif //DRAGPLAYERCOMMAND_H_
