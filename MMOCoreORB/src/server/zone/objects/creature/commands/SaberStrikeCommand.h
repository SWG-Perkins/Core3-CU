/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERSTRIKECOMMAND_H_
#define SABERSTRIKECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberStrikeCommand : public CombatQueueCommand {
public:

	SaberStrikeCommand(const String& name, ZoneProcessServer* server)
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
			animationCRC = String("showoff_1_light").hashCode();
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = String("combo_5a_light").hashCode();

		return doCombatAction(creature, target);
	}

};

#endif //SABERSTRIKECOMMAND_H_
