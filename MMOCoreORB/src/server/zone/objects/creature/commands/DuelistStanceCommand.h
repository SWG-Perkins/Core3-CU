/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DUELISTSTANCECOMMAND_H_
#define DUELISTSTANCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DuelistStanceCommand : public QueueCommand {
public:

	DuelistStanceCommand(const String& name, ZoneProcessServer* server)
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

#endif //DUELISTSTANCECOMMAND_H_
