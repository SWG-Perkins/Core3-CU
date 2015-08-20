/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef CYBORGCRITICALSNIPECOMMAND_H_
#define CYBORGCRITICALSNIPECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CyborgCriticalSnipeCommand : public QueueCommand {
public:

	CyborgCriticalSnipeCommand(const String& name, ZoneProcessServer* server)
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

#endif //CYBORGCRITICALSNIPECOMMAND_H_
