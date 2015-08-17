/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef TRAUMATIZECOMMAND_H_
#define TRAUMATIZECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class TraumatizeCommand : public QueueCommand {
public:

	TraumatizeCommand(const String& name, ZoneProcessServer* server)
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

#endif //TRAUMATIZECOMMAND_H_
