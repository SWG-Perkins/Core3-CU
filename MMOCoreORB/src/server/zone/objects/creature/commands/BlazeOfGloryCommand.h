/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef BLAZEOFGLORYCOMMAND_H_
#define BLAZEOFBLORYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BlazeOfGloryCommand : public QueueCommand {
public:

	BlazeOfGloryCommand(const String& name, ZoneProcessServer* server)
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

#endif //BLAZEOFGLORYCOMMAND_H_
