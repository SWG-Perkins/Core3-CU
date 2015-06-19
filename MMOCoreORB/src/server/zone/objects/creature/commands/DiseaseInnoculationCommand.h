/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef DISEASEINNOCULATIONCOMMAND_H_
#define DISEASEINNOCULATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DiseaseInnoculationCommand : public QueueCommand {
public:

	DiseaseInnoculationCommand(const String& name, ZoneProcessServer* server)
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

#endif //DISEASEINNOCULATIONCOMMAND_H_
