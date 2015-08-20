/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERBLINDCOMMAND_H_
#define SABERBLINDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberBlindCommand : public CombatQueueCommand {
public:

	SaberBlindCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getWeapon()->isJediOneHandedWeapon())
			animationCRC = String("combo_jedi_2_light").hashCode();
		else if (creature->getWeapon()->isJediTwoHandedWeapon())
			animationCRC = String("combo_3c_light").hashCode();
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = String("combo_4a_light").hashCode();

		return doCombatAction(creature, target);
	}

};

#endif //SABERBLINDCOMMAND_H_
