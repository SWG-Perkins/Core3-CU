/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERBODYHITCOMMAND_H_
#define SABERBODYHITCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberBodyHitCommand : public CombatQueueCommand {
public:

	SaberBodyHitCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getWeapon()->isJediOneHandedWeapon())
			animationCRC = String("combo_3c_light").hashCode();
		else if (creature->getWeapon()->isJediTwoHandedWeapon())
			animationCRC = 0; // Can't find it
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = String("combo_3a_light").hashCode();

		return doCombatAction(creature, target);
	}

};

#endif //SABERBODYHITCOMMAND_H_
