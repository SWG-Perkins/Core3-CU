/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEBREACHCOMMAND_H_
#define FORCEBREACHCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"

class ForceBreachCommand : public ForcePowersQueueCommand {
public:

	ForceBreachCommand(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature))
			return NOJEDIARMOR;

		Reference<SceneObject*> object = server->getZoneServer()->getObject(target);
		ManagedReference<CreatureObject*> creatureTarget = object.castTo<CreatureObject*>();

		if (creatureTarget == NULL)
			return INVALIDTARGET;

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {
	/*		BuffList* targetBuffList = creatureTarget->getBuffList();

			if (!(targetBuffList->size() > 0))
				return GENERALERROR;

			for (int i = 0; i < targetBuffList->size(); i++) {
				ManagedReference<Buff*> buff = targetBuffList->getValueAt(i);

				if (buff->getBuffName().contains("force") && !buff->isDebuff())
					creature->removeBuff(buff->getBuffName().hashCode());
			}*/
		}

		return res;
	}

};

#endif //FORCEBREACHCOMMAND_H_
