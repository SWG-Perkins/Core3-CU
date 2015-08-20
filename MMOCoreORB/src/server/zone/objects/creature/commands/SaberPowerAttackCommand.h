/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERPOWERATTACKCOMMAND_H_
#define SABERPOWERATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberPowerAttackCommand : public CombatQueueCommand {
public:

	SaberPowerAttackCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getWeapon()->isJediOneHandedWeapon())
			animationCRC = String("showoff_1_light").hashCode();
		else if (creature->getWeapon()->isJediTwoHandedWeapon())
			animationCRC = String("combo_jedi_1_light").hashCode();
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = String("combo_3d_light").hashCode();

		return doCombatAction(creature, target);
	}

};

#endif //SABERPOWERATTACKCOMMAND_H_
