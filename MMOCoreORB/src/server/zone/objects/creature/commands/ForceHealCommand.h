/*
 * ForceHealCommand.h
 *
 *  Created on: Sep 10, 2013
 *      Author: Dreadlow
 */

#ifndef FORCEHEALCOMMAND_H_
#define FORCEHEALCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceHealCommand : public QueueCommand {
	int forceCost;
	int healthHealed;
	int range;
public:

	ForceHealCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		forceCost = 0;
		healthHealed = 0;
		range = 32;
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) {

		if (!creatureTarget->isPlayerCreature())
			return false;

		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget))
			return false;

		if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH)) {
			if (creature != creatureTarget)
				creature->sendSystemMessage("@jedi_spam:no_damage_heal_other");
			else
				creature->sendSystemMessage("@jedi_spam:no_damage_heal_self");

			return false;
		}

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");
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

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (!object->isCreatureObject()) {
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());

				if (tangibleObject != NULL && tangibleObject->isAttackableBy(creature))
					object = creature;
				else {
					creature->sendSystemMessage("@jedi_spam:not_this_target");
					return GENERALERROR;
				}
			}
		} else
			object = creature;

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingMount() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;
		else
			Locker clocker(creatureTarget, creature);

		if (!creature->isInRange(creatureTarget, range))
			return TOOFAR;

		if (!canPerformSkill(creature, creatureTarget))
			return GENERALERROR;

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject->getForcePower() <= 100) {
			creature->sendSystemMessage("@jedi_spam:no_force_power");
			return GENERALERROR;
		}

		if (playerObject->hasAbility("forceHeal_2"))
			healthHealed = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, 1500);
		else if (playerObject->hasAbility("forceHeal_1"))
			healthHealed = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, 1000);
		else
			healthHealed = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, 500);

		if (healthHealed > 0) {
			if (creature != creatureTarget) {
				StringIdChatParameter healOtherSelf("jedi_spam", "heal_other_self");
				healOtherSelf.setTT(creatureTarget->getFirstName());
				healOtherSelf.setDI(healthHealed);
				healOtherSelf.setTO("@jedi_spam:health_damage");
				creature->sendSystemMessage(healOtherSelf);

				StringIdChatParameter healOtherOther("jedi_spam", "heal_other_other");
				healOtherOther.setDI(healthHealed);
				healOtherOther.setTO("@jedi_spam:health_damage");
				healOtherOther.setTT(creature->getFirstName());
				creatureTarget->sendSystemMessage(healOtherOther);
			} else {
				StringIdChatParameter healSelf("jedi_spam", "heal_self");
				healSelf.setDI(healthHealed);
				healSelf.setTO("@jedi_spam:health_damage");
				creature->sendSystemMessage(healSelf);
			}
		}

		if (creatureTarget != creature)
			creature->doCombatAnimation(creatureTarget, String("force_healing_1").hashCode(), 0, 0);
		else
			creature->playEffect("clienteffect/pl_force_healing.cef");

		forceCost = MIN((healthHealed / 15), 100);
		playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		return SUCCESS;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) {
		return defaultTime * 3.0;
	}
};

#endif //FORCEHEALCOMMAND_H_
