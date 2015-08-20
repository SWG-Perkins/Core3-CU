/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CYBORGKICKDOWNCOMMAND_H_
#define CYBORGKICKDOWNCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CyborgKickDownCommand : public QueueCommand {
public:

	CyborgKickDownCommand(const String& name, ZoneProcessServer* server)
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

#endif //CYBORGKICKDOWNCOMMAND_H_
