/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef INTIMIDATECOMMAND_H_
#define INTIMIDATECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class IntimidateCommand : public QueueCommand {
public:

	IntimidateCommand(const String& name, ZoneProcessServer* server)
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

#endif //INTIMIDATECOMMAND_H_
