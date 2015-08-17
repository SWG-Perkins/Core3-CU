/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEFEEDBACKCOMMAND_H_
#define FORCEFEEDBACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceFeedbackCommand : public QueueCommand {
public:

	ForceFeedbackCommand(const String& name, ZoneProcessServer* server)
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

#endif //FORCEFEEDBACKCOMMAND_H_
