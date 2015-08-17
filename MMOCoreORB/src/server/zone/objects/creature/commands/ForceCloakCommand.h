/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCECLOAKCOMMAND_H_
#define FORCECLOAKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/events/ForceCloakEventTask.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"
#include "server/zone/objects/creature/buffs/BuffCRC.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"

class ForceCloakCommand : public QueueCommand {
public:

	ForceCloakCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<Zone*> zone = creature->getZone();

		if (zone == NULL)
			return GENERALERROR;

		Locker zoneLocker(zone);

		if (!creature->isInvisible()) {
			int forceCost = 150;

			ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

			if (playerObject->getForcePower() <= forceCost) {
				creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to perform that action.
				return GENERALERROR;
			}

			SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = creature->getCloseObjects();

			for (int i = 0; i < closeObjects->size(); ++i) {
				SceneObject* scno = cast<SceneObject*>( closeObjects->get(i).get());

				if (scno != creature && scno->isCreatureObject() && creature->isInRange(scno, 20)) {
					creature->sendSystemMessage("@cbt_spam:cover_fail_target_near");
					return GENERALERROR;
				}
			}

			playerObject->setForcePower(playerObject->getForcePower() - forceCost);

			PlayClientEffectLoc* cloakEffectOther1 = new PlayClientEffectLoc("clienteffect/pl_force_speed_self.cef", zone->getZoneName(), creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());
			creature->broadcastMessage(cloakEffectOther1, false);

			PlayClientEffectLoc* cloakEffectOther2 = new PlayClientEffectLoc("clienteffect/combat_special_attacker_cover.cef", zone->getZoneName(), creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());
			creature->broadcastMessage(cloakEffectOther2, false);

			creature->playEffect("clienteffect/pl_force_speed_self.cef");
			creature->playEffect("clienteffect/combat_special_attacker_cover.cef");

			creature->showFlyText("combat_effects", "go_cloak", 1.0, 255, 0, 0);

			creature->clearCombatState(true);

		//	creature->addBuff(nameCRC);

			for (int i = 0; i < closeObjects->size(); ++i) {
				SceneObject* scno = cast<SceneObject*>( closeObjects->get(i).get());

				if (scno != creature && scno->isPlayerCreature())
					scno->notifyDissapear(creature);
			}

			creature->setInvisible(true);
			creature->setVisible(0);

			CreatureObjectDeltaMessage6* msg = new CreatureObjectDeltaMessage6(creature);
			msg->updateVisible();
			msg->close();
			creature->broadcastMessage(msg, true);

			creature->setSpeedMultiplierMod(0.75f);

			creature->sendSystemMessage("@jedi_spam:apply_forcecloak");

			Reference<ForceCloakEventTask*> forceCloakEventTask = new ForceCloakEventTask(creature);
			forceCloakEventTask->run();
		} else {
			if (creature->hasBuff(nameCRC))
				creature->removeBuff(nameCRC);

			creature->setInvisible(false);
			creature->setVisible(1);

			CreatureObjectDeltaMessage6* msg = new CreatureObjectDeltaMessage6(creature);
			msg->updateVisible();
			msg->close();
			creature->broadcastMessage(msg, true);

			creature->setSpeedMultiplierMod(1.0f);

			SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = creature->getCloseObjects();

			for (int i = 0; i < closeObjects->size(); ++i) {
				SceneObject* scno = cast<SceneObject*>( closeObjects->get(i).get());

				if (scno != creature && scno->isPlayerCreature())
					scno->notifyInsert(creature);
			}

			PlayClientEffectLoc* removeCloakEffectOther = new PlayClientEffectLoc("clienteffect/combat_special_attacker_cover.cef", zone->getZoneName(), creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());
			creature->broadcastMessage(removeCloakEffectOther, false);

			creature->playEffect("clienteffect/combat_special_attacker_cover.cef");

			creature->showFlyText("combat_effects", "no_cloak", 1.0, 255, 0, 0);

			creature->sendSystemMessage("@jedi_spam:remove_forcecloak");
		}

		return SUCCESS;
	}

};

#endif //FORCECLOAKCOMMAND_H_
