/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef SABERARMORBREAKCOMMAND_H_
#define SABERARMORBREAKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SaberArmorBreakCommand : public CombatQueueCommand {
public:

	SaberArmorBreakCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL)
			return INVALIDTARGET;

		if (creature->getWeapon()->isJediOneHandedWeapon())
			animationCRC = String("combo_jedi_1_light").hashCode();
		else if (creature->getWeapon()->isJediTwoHandedWeapon())
			animationCRC = String("combo_3b_light").hashCode();
		else if (creature->getWeapon()->isJediPolearmWeapon())
			animationCRC = String("combo_2c_light").hashCode();

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {
			CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		//	if (!creatureTarget->hasBuff(nameCRC) && !creatureTarget->hasBuff(BuffCRC::ARMORBREAK_IMMUNITY))
		//		creatureTarget->addBuff(nameCRC);
		}

		return res;
	}

};

#endif //SABERARMORBREAKCOMMAND_H_
