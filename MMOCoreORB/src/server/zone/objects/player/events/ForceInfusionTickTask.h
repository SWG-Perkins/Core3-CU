/*
 * ForceInfusionRegenTask.h
 *
 *  Created on: Nov. 09, 2014
 *      Author: Dreadlow
 */

#ifndef FORCEINFUSIONTICKTASK_H_
#define FORCEINFUSIONTICKTASK_H_


#include "server/zone/objects/creature/CreatureObject.h"

class ForceInfusionTickTask : public Task {
	ManagedReference<CreatureObject*> creature;
	int counter;
	int amountOfTicks;
	int amount;
public:

	ForceInfusionTickTask(CreatureObject* creo, int healing) {
		creature = creo;  // This is the Attacker
		counter = 0;
		amountOfTicks = 5;
		amount = healing;
	}

	void run() {
		Locker lockerC(creature);

		if(creature != NULL) {
			if (counter < amountOfTicks && !creature->isIncapacitated() && !creature->isDead()) {
				if (creature->hasDamage(CreatureAttribute::HEALTH))
					creature->healDamage(creature, CreatureAttribute::HEALTH, amount, true);

				counter++;
				reschedule(6000); // Reschedule in 6 seconds...
			} else
				creature->removePendingTask("forceInfusionTickTask");
		}
	}
};


#endif /* FORCEINFUSIONTICKTASK_H_ */
