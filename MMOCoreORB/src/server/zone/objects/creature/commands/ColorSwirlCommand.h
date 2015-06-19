/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef COLORSWIRLCOMMAND_H_
#define COLORSWIRLCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ColorSwirlCommand : public QueueCommand {
public:

	ColorSwirlCommand(const String& name, ZoneProcessServer* server)
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

#endif //COLORSWIRLCOMMAND_H_
