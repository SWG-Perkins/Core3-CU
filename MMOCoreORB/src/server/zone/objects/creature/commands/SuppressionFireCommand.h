/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SUPPRESSIONFIRECOMMAND_H_
#define SUPPRESSIONFIRECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SuppressionFireCommand : public CombatQueueCommand {
public:

	SuppressionFireCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;


		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {
			Reference<SceneObject*> object = server->getZoneServer()->getObject(target);
			ManagedReference<CreatureObject*> creatureTarget = object.castTo<CreatureObject*>();

			if (creatureTarget == NULL)
				return GENERALERROR;

			//creatureTarget->addBuff(nameCRC);
		}

		return res;
	}

};

#endif //SUPPRESSIONFIRECOMMAND_H_
