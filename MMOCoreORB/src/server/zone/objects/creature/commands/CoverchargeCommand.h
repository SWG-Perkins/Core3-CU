/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef COVERCHARGECOMMAND_H_
#define COVERCHARGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CoverchargeCommand : public QueueCommand {
public:

	CoverchargeCommand(const String& name, ZoneProcessServer* server)
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

#endif //COVERCHARGECOMMAND_H_
