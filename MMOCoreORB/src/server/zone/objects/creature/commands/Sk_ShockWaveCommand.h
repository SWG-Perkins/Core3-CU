/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SK_SHOCKWAVECOMMAND_H_
#define SK_SHOCKWAVECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class Sk_ShockWaveCommand : public QueueCommand {
public:

	Sk_ShockWaveCommand(const String& name, ZoneProcessServer* server)
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

#endif //SK_SHOCKWAVECOMMAND_H_
