/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERHITCOMMAND_H_
#define SABERHITCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberHitCommand : public CombatQueueCommand {
public:

	SaberHitCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getWeapon()->isJediOneHandedWeapon())
			animationCRC = String("combo_jedi_1_light").hashCode();
		else if (creature->getWeapon()->isJediTwoHandedWeapon())
			animationCRC = String("combo_2c_light").hashCode();
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = String("combo_3a_light").hashCode();

		return doCombatAction(creature, target);
	}

};

#endif //SABERHITCOMMAND_H_
