/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef INSIDIOUSMALADYCOMMAND_H_
#define INSIDIOUSMALADYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class InsidiousMaladyCommand : public QueueCommand {
public:

	InsidiousMaladyCommand(const String& name, ZoneProcessServer* server)
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

#endif //INSIDIOUSMALADYCOMMAND_H_
