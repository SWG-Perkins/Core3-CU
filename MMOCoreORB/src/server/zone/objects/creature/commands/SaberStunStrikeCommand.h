/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERSTUNSTRIKECOMMAND_H_
#define SABERSTUNSTRIKECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberStunStrikeCommand : public CombatQueueCommand {
public:

	SaberStunStrikeCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getWeapon()->isJediOneHandedWeapon())
			animationCRC = String("combo_2b_light").hashCode();
		else if (creature->getWeapon()->isJediTwoHandedWeapon())
			animationCRC = String("combo_4a_light").hashCode();
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = String("showoff_2_light").hashCode();

		return doCombatAction(creature, target);;
	}

};

#endif //SABERSTUNSTRIKECOMMAND_H_
