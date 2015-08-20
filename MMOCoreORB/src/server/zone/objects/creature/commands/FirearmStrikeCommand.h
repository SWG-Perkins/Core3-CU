/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FIREARMSTRIKECOMMAND_H_
#define FIREARMSTRIKECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class FirearmStrikeCommand : public QueueCommand {
public:

	FirearmStrikeCommand(const String& name, ZoneProcessServer* server)
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

#endif //FIREARMSTRIKECOMMAND_H_
