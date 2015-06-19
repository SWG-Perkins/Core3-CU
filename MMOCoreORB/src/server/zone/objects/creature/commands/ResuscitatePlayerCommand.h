/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef RESUSCITATEPLAYERCOMMAND_H_
#define RESUSCITATEPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ResuscitatePlayerCommand : public QueueCommand {
public:

	ResuscitatePlayerCommand(const String& name, ZoneProcessServer* server)
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

#endif //RESUSCITATEPLAYERCOMMAND_H_
