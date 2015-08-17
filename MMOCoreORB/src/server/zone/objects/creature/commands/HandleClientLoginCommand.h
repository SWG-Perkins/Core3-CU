/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef HANDLECLIENTLOGINCOMMAND_H_
#define HANDLECLIENTLOGINCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HandleClientLoginCommand : public QueueCommand {
public:

	HandleClientLoginCommand(const String& name, ZoneProcessServer* server)
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

#endif //HANDLECLIENTLOGINCOMMAND_H_
