/*
Copyright (C) 2014 CU Galaxies
*/

#ifndef FORCEINFUSIONCOMMAND_H_
#define FORCEINFUSIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/events/ForceInfusionTickTask.h"
#include "server/zone/objects/creature/buffs/BuffCRC.h"

class ForceInfusionCommand : public QueueCommand {
	int healingAmount;
public:

	ForceInfusionCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		healingAmount = 0;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject->getForcePower() <= 10) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to perform that action.
			return GENERALERROR;
		}

		Reference<ForceInfusionTickTask*> infusionCheck = creature->getPendingTask("forceInfusionTickTask").castTo<ForceInfusionTickTask*>();

		if (infusionCheck != NULL || creature->hasBuff(String("forceinfusion").hashCode()) || creature->hasBuff(String("forceinfusion_1").hashCode()))
			return GENERALERROR;

		//creature->addBuff(String("forceinfusion_1").hashCode());

		if (name.contains("_1"))
			healingAmount = 150;
		else
			healingAmount = 75;

		Reference<ForceInfusionTickTask*> fitTask = new ForceInfusionTickTask(creature, healingAmount);
		fitTask->run();

		creature->playEffect("clienteffect/pl_force_heal_self.cef");

		creature->sendSystemMessage("@jedi_spam:apply_" + name.toLowerCase() + "_1");

		playerObject->setForcePower(playerObject->getForcePower() - 10);

		return SUCCESS;
	}

};

#endif //FORCEINFUSIONCOMMAND_H_
