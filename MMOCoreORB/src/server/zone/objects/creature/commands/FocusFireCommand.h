/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FOCUSFIRECOMMAND_H_
#define FOCUSFIRECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class FocusFireCommand : public QueueCommand {
public:

	FocusFireCommand(const String& name, ZoneProcessServer* server)
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

#endif //FOCUSFIRECOMMAND_H_
