/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef BACTASHOTCOMMAND_H_
#define BACTASHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class BactaShotCommand : public QueueCommand {
public:

	BactaShotCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) {

			if (!creatureTarget->isPlayerCreature())
				return false;

			PlayerManager* playerManager = server->getPlayerManager();

			if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget))
				return false;

			if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH)) {
				if (creature != creatureTarget)
					creature->showFlyText("combat_effects", "target_invalid_fly", 0x02, 0x84, 0x82);
				else
					creature->showFlyText("combat_effects", "target_invalid_fly", 0x02, 0x84, 0x82);

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
						creature->showFlyText("combat_effects", "target_invalid_fly", 0x02, 0x84, 0x82);
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

			if (!canPerformSkill(creature, creatureTarget))
				return GENERALERROR;



			uint32 healthHealed = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, 500);


			if (creatureTarget != creature)
				creature->doAnimation("heal_other");
			else
				creature->playEffect("clienteffect/medic_heal.cef");
				creature->doAnimation("heal_self");

			return SUCCESS;
		}

};

#endif //BACTASHOTCOMMAND_H_
