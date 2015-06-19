/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEINTIMIDATECOMMAND_H_
#define FORCEINTIMIDATECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceIntimidateCommand : public QueueCommand {
public:

	ForceIntimidateCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCEINTIMIDATECOMMAND_H_
