/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCESUPPRESSIONCOMMAND_H_
#define FORCESUPPRESSIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"

class ForceSuppressionCommand : public ForcePowersQueueCommand {
public:

	ForceSuppressionCommand(const String& name, ZoneProcessServer* server)
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

		//if (creatureTarget->isImpaired() || creatureTarget->isMezzed() || creatureTarget->hasBuff(BuffCRC::ROOT_IMMUNITY) || creatureTarget->hasBuff(BuffCRC::BOSS_ROOT_IMMUNITY))
			return GENERALERROR;

		int res = doCombatAction(creature, target);

		if (res == SUCCESS)
		//	creatureTarget->addBuff(nameCRC);

		return res;
	}

};

#endif //FORCESUPPRESSIONCOMMAND_H_
