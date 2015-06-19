/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DOMINATEMINDCOMMAND_H_
#define DOMINATEMINDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DominateMindCommand : public QueueCommand {
public:

	DominateMindCommand(const String& name, ZoneProcessServer* server)
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

#endif //DOMINATEMINDCOMMAND_H_
