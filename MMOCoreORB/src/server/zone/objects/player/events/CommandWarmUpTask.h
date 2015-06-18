/*
 * CommandWarmUpTask.h
 *
 *  Created on: Nov 10, 2014
 *      Author: dreadlow
 */

#ifndef COMMANDWARMUPTASK_H_
#define COMMANDWARMUPTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"

class CommandWarmUpTask : public Task {
	ManagedReference<CreatureObject*> creature;
	uint32 actionCRC;
	uint32 actionCount;
	uint64 targetID;
	UnicodeString arguments;
public:

	CommandWarmUpTask(CreatureObject* creo, uint32 crc, uint32 count, uint64 target, UnicodeString args) {
		creature = creo;  // This is the Attacker
		actionCRC = crc;
		actionCount = count;
		targetID = target;
		arguments = args;
	}

	void run() {
		Locker lockerC(creature);

		if (creature != NULL)
			creature->enqueueCommand(actionCRC, actionCount, targetID, arguments);
	}
};

#endif /* COMMANDWARMUPTASK_H_ */
