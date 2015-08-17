/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERSPINATTACKCOMMAND_H_
#define SABERSPINATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberSpinAttackCommand : public CombatQueueCommand {
public:

	SaberSpinAttackCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getWeapon()->isJediOneHandedWeapon())
			animationCRC = String("showoff_2_light").hashCode();
		else if (creature->getWeapon()->isJediTwoHandedWeapon())
			animationCRC = String("showoff_1_light").hashCode();
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = String("showoff_1_light").hashCode();

		return doCombatAction(creature, target);
	}

};

#endif //SABERSPINATTACKCOMMAND_H_
