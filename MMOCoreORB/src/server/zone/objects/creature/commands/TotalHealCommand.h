/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef TOTALHEALCOMMAND_H_
#define TOTALHEALCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class TotalHealCommand : public QueueCommand {
public:

	TotalHealCommand(const String& name, ZoneProcessServer* server)
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

#endif //TOTALHEALCOMMAND_H_
