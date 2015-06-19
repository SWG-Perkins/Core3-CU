/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef HEALSTATESCOMMAND_H_
#define HEALSTATESCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HealStatesCommand : public QueueCommand {
public:

	HealStatesCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	bool canPerformSkill(CreatureObject* creature) {
		if (!creature->hasState(CreatureState::STUNNED) && !creature->hasState(CreatureState::DIZZY)
				&& !creature->hasState(CreatureState::INTIMIDATED) && !creature->hasState(CreatureState::BLINDED)) {
			creature->sendSystemMessage("@healing_response:healing_response_72");
			return false;
		}

		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature))
			return NOJEDIARMOR;

		if (!canPerformSkill(creature))
			return GENERALERROR;

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject->getForcePower() <= 100) {
			creature->sendSystemMessage("@jedi_spam:no_force_power");
			return GENERALERROR;
		}

		if (creature->hasStates()) {
			if (creature->hasState(CreatureState::STUNNED))
				creature->removeBuff(String("stun").hashCode());

			if (creature->hasState(CreatureState::DIZZY))
				creature->removeBuff(String("dizzy").hashCode());

			if (creature->hasState(CreatureState::BLINDED))
				creature->removeBuff(String("blind").hashCode());

			if (creature->hasState(CreatureState::INTIMIDATED))
				creature->removeBuff(String("intimidate").hashCode());

			creature->playEffect("clienteffect/pl_force_heal_self.cef", "");
			playerObject->setForcePower(playerObject->getForcePower() - 100);
		}

		return SUCCESS;
	}

};

#endif //HEALSTATESCOMMAND_H_
