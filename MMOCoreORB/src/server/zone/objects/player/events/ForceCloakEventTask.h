/*
 * ForceCloakEventTask.h
 *
 *  Created on: Nov 3, 2014
 *      Author: dreadlow
 */

#ifndef FORCECLOAKEVENTTASK_H_
#define FORCECLOAKEVENTTASK_H_

#include "engine/engine.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"
#include "server/zone/objects/creature/buffs/BuffCRC.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"

class ForceCloakEventTask: public Task {
	ManagedReference<CreatureObject*> creature;
	ManagedReference<PlayerObject*> player;

public:
	ForceCloakEventTask(CreatureObject* cr) {
		creature = cr;
		player = creature->getPlayerObject();
	}

	void run() {
		Locker playerLocker(creature);

		try {
			if (creature->isInvisible()) {
				int forceCost = 25;

				SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = creature->getCloseObjects();

				for (int i = 0; i < closeObjects->size(); ++i) {
					SceneObject* scno = cast<SceneObject*>( closeObjects->get(i).get());

					if (scno != creature && scno->isCreatureObject() && creature->isInRange(scno, 20))
						forceCost += 25;
				}

				if (player->getForcePower() >= forceCost) {
					player->setForcePower(player->getForcePower() - forceCost);
					reschedule(10000);
				} else {
					if (creature->hasBuff(String("forcecloak").hashCode()))
						creature->removeBuff(String("forcecloak").hashCode());

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

					PlayClientEffectLoc* removeCloakEffectOther = new PlayClientEffectLoc("clienteffect/combat_special_attacker_cover.cef", creature->getZone()->getZoneName(), creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());
					creature->broadcastMessage(removeCloakEffectOther, false);

					creature->playEffect("clienteffect/combat_special_attacker_cover.cef");

					creature->showFlyText("combat_effects", "no_cloak", 1.0, 255, 0, 0);

					creature->sendSystemMessage("@jedi_spam:remove_forcecloak");
				}
			}

		} catch (Exception& e) {
			creature->error("unreported exception caught in ForceMeditateTask::activate");
		}
	}

};

#endif /* FORCECLOAKEVENTTASK_H_ */
