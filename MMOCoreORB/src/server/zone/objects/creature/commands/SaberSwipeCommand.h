/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERSWIPECOMMAND_H_
#define SABERSWIPECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberSwipeCommand : public CombatQueueCommand {
public:

	SaberSwipeCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getWeapon()->isJediOneHandedWeapon())
			animationCRC = String("combo_jedi_3_light").hashCode();
		else if (creature->getWeapon()->isJediTwoHandedWeapon())
			animationCRC = String("showoff_2_light").hashCode();
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = 0; // Can't find

		return doCombatAction(creature, target);
	}

};

#endif //SABERSWIPECOMMAND_H_
