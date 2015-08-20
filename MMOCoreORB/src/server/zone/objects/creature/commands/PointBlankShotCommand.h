/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef POINTBLANKSHOTCOMMAND_H_
#define POINTBLANKSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PointBlankShotCommand : public QueueCommand {
public:

	PointBlankShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //POINTBLANKSHOTCOMMAND_H_
