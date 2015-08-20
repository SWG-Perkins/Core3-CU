/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERLEGHITCOMMAND_H_
#define SABERLEGHITCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberLegHitCommand : public CombatQueueCommand {
public:

	SaberLegHitCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getWeapon()->isJediOneHandedWeapon())
			animationCRC = String("combo_4c_light").hashCode();
		else if (creature->getWeapon()->isJediTwoHandedWeapon())
			animationCRC = String("combo_3b_light").hashCode();
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = String("combo_3b_light").hashCode();

		return doCombatAction(creature, target);
	}

};

#endif //SABERLEGHITCOMMAND_H_
