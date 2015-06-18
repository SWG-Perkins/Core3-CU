/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERSLASHCOMMAND_H_
#define SABERSLASHCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberSlashCommand : public CombatQueueCommand {
public:

	SaberSlashCommand(const String& name, ZoneProcessServer* server)
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
			animationCRC = String("combo_3d_light").hashCode();
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = String("combo_2d_light").hashCode();

		return doCombatAction(creature, target);;
	}

};

#endif //SABERSLASHCOMMAND_H_
