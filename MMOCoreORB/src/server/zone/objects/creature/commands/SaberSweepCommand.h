/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERSWEEPCOMMAND_H_
#define SABERSWEEPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberSweepCommand : public CombatQueueCommand {
public:

	SaberSweepCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getWeapon()->isJediOneHandedWeapon())
			animationCRC = 0; // Can't find
		else if (creature->getWeapon()->isJediTwoHandedWeapon())
			animationCRC = String("combo_4c_light").hashCode();
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = 0; // Can't find

		return doCombatAction(creature, target);
	}

};

#endif //SABERSWEEPCOMMAND_H_
