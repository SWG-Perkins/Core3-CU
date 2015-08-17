/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEWEAKENCOMMAND_H_
#define FORCEWEAKENCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"

class ForceWeakenCommand : public ForcePowersQueueCommand {
public:

	ForceWeakenCommand(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

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

		//if (creatureTarget->isImpaired() || creatureTarget->isMezzed() || creatureTarget->hasBuff(BuffCRC::SNARE_IMMUNITY) || creatureTarget->hasBuff(BuffCRC::BOSS_SNARE_IMMUNITY))
			return GENERALERROR;

		int res = doCombatAction(creature, target);

		if (res == SUCCESS)
		//	creatureTarget->addBuff(nameCRC);

		return res;
	}

};

#endif //FORCEWEAKENCOMMAND_H_
