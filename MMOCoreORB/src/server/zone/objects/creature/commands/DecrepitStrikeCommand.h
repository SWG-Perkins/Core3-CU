/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DECREPITSTRIKECOMMAND_H_
#define DECREPITSTRIKECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DecrepitStrikeCommand : public QueueCommand {
public:

	DecrepitStrikeCommand(const String& name, ZoneProcessServer* server)
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

#endif //DECREPITSTRIKECOMMAND_H_
