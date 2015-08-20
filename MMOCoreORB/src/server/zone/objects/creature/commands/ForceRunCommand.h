/*
Copyright (C) 2014 CU Galaxies
 */

#ifndef FORCERUNCOMMAND_H_
#define FORCERUNCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceRunCommand : public QueueCommand {
	int forceCost;
public:
	ForceRunCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		forceCost = 0;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature))
			return NOJEDIARMOR;

	//	if (name.contains("_2"))
			//forceCost = 200;
		//else if (name.contains("_1"))
			//forceCost = 150;
		//else
			//forceCost = 100;

		if (!creature->hasBuff(nameCRC)) {

			if((creature->hasBuff(BuffCRC::FORCERUN)) || (creature->hasBuff(BuffCRC::FORCERUN_1))
					|| (creature->hasBuff(BuffCRC::FORCERUN_2)) || (creature->hasBuff(String("burstrun").hashCode()))
					|| (creature->hasBuff(String("retreat").hashCode()))) {
				creature->sendSystemMessage("@jedi_spam:force_run_wont_stack");
				return GENERALERROR;
			}

			//Check for and deduct Force cost.
			ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

			if (playerObject->getForcePower() <= forceCost)
				return INSUFFICIENTFORCE;

			playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		//	creature->addBuff(nameCRC);

			return SUCCESS;
		} else {
			creature->removeBuff(nameCRC);
			return SUCCESS;
		}
	}



};

#endif //FORCERUNCOMMAND_H_
