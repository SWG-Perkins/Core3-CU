/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CYBORGSTRENGTHBUFFCOMMAND_H_
#define CYBORGSTRENGTHBUFFCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CyborgStrengthBuffCommand : public QueueCommand {
public:

	CyborgStrengthBuffCommand(const String& name, ZoneProcessServer* server)
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

#endif //CYBORGSTRENGTHBUFFCOMMAND_H_
