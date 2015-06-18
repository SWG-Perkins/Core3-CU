/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
 */

#include "CommandConfigManager.h"
#include "server/zone/objects/creature/commands/commands.h"
#include "server/zone/objects/creature/commands/effect/StateEffect.h"
#include "server/zone/objects/creature/commands/effect/DotEffect.h"
#include "server/zone/objects/creature/commands/effect/CommandEffect.h"

#include "server/zone/objects/creature/commands/pet/PetAttackCommand.h"
#include "server/zone/objects/creature/commands/pet/PetEmoteCommand.h"
#include "server/zone/objects/creature/commands/pet/PetFeedCommand.h"
#include "server/zone/objects/creature/commands/pet/PetFollowCommand.h"
#include "server/zone/objects/creature/commands/pet/PetGroupCommand.h"
#include "server/zone/objects/creature/commands/pet/PetRechargeCommand.h"
#include "server/zone/objects/creature/commands/pet/PetRechargeOtherCommand.h"
#include "server/zone/objects/creature/commands/pet/PetRecoverCommand.h"
#include "server/zone/objects/creature/commands/pet/PetStayCommand.h"
#include "server/zone/objects/creature/commands/pet/PetStoreCommand.h"
#include "server/zone/objects/creature/commands/pet/PetTrickCommand.h"
#include "server/zone/objects/creature/commands/pet/PetTransferCommand.h"

#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/creature/CreaturePosture.h"
#include "server/zone/objects/creature/CreatureLocomotion.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"

#include "server/zone/ZoneProcessServer.h"
#include "CommandList.h"

CommandList* CommandConfigManager::slashCommands = NULL;
ZoneProcessServer* CommandConfigManager::server = NULL;
int CommandConfigManager::ERROR_CODE = 0;

CommandConfigManager::CommandConfigManager(ZoneProcessServer* serv) {
	server = serv;

	init();

	setLogging(false);
	setLoggingName("CommandConfigManager");

	registerFunctions();
	registerGlobals();
	registerCommands();
}

CommandConfigManager::~CommandConfigManager() {
	server = NULL;

	if (slashCommands != NULL)
		delete slashCommands;

	slashCommands = NULL;

	ERROR_CODE = 0;
}

void CommandConfigManager::loadCommandData(const String& filename) {
	int num = 0;

	IffStream* metatable = TemplateManager::instance()->openIffFile(filename);

	if (metatable == NULL) {
		error("Could not load command table " + filename + ".");
		return;
	}

	DataTableIff tablesToLoad;
	tablesToLoad.readObject(metatable);

	delete metatable;

	for (int j = 0; j < tablesToLoad.getTotalRows(); ++j) {
		DataTableRow* tableRow = tablesToLoad.getRow(j);
		String tableName;
		tableRow->getValue(0, tableName);


		IffStream* iffStream = TemplateManager::instance()->openIffFile(tableName);

		if (iffStream == NULL) {
			error("Could not load commands from " + tableName + ".");
			return;
		} else
			info("opened " + tableName);

		DataTableIff dtiff;
		dtiff.readObject(iffStream);

		delete iffStream;

		for (int i = 0; i < dtiff.getTotalRows(); ++i) {
			DataTableRow* row = dtiff.getRow(i);
			QueueCommand* slashCommand;

			bool disabled; // check disabled first and don't load it

			String name;
			bool combat = false;
			int targetType;
			float maxRangeToTarget;
			String characterAbility;
			float defaultTime;
			int defaultPriority;
			uint64 stateMask = 0; // need to construct statemask
			bool state;
			bool position; // need to add positions one by one

			row->getValue(CommandConfigManager::COMMANDNAME, name);
			slashCommand = createCommand(name.trim().toLowerCase());;

			if (slashCommand == NULL) {
				error("Could not create command " + name);
				continue;
			}

			if (!tableName.contains("space"))
				row->getValue(CommandConfigManager::ADDTOCOMBATQUEUE, combat);

			slashCommand->setAddToCombatQueue(combat);

			row->getValue(CommandConfigManager::TARGETTYPE, targetType);
			slashCommand->setTargetType(targetType);

			row->getValue(CommandConfigManager::MAXRANGETOTARGET, maxRangeToTarget);
			slashCommand->setMaxRange(maxRangeToTarget);

			row->getValue(CommandConfigManager::CHARACTERABILITY, characterAbility);
			slashCommand->setCharacterAbility(characterAbility);

			row->getValue(CommandConfigManager::DEFAULTTIME, defaultTime);
			slashCommand->setDefaultTime(defaultTime);

			row->getValue(CommandConfigManager::DEFAULTPRIORITY, defaultPriority);
			slashCommand->setDefaultPriority(defaultPriority);

			// build state mask
			row->getValue(CommandConfigManager::COVER, state);
			if (!state) stateMask |= CreatureState::COVER;
			row->getValue(CommandConfigManager::COMBAT, state);
			if (!state) stateMask |= CreatureState::COMBAT;
			row->getValue(CommandConfigManager::PEACE, state);
			if (!state) stateMask |= CreatureState::PEACE;
			row->getValue(CommandConfigManager::AIMING, state);
			if (!state) stateMask |= CreatureState::AIMING;
			row->getValue(CommandConfigManager::ALERT, state);
			if (!state) stateMask |= CreatureState::ALERT;
			row->getValue(CommandConfigManager::BERSERK, state);
			if (!state) stateMask |= CreatureState::BERSERK;
			row->getValue(CommandConfigManager::FEIGNDEATH, state);
			if (!state) stateMask |= CreatureState::FEIGNDEATH;
			row->getValue(CommandConfigManager::COMBATATTITUDEEVASIVE, state);
			if (!state) stateMask |= CreatureState::COMBATATTITUDEEVASIVE;
			row->getValue(CommandConfigManager::COMBATATTITUDENORMAL, state);
			if (!state) stateMask |= CreatureState::COMBATATTITUDENORMAL;
			row->getValue(CommandConfigManager::COMBATATTITUDEAGGRESSIVE, state);
			if (!state) stateMask |= CreatureState::COMBATATTITUDEAGGRESSIVE;
			row->getValue(CommandConfigManager::TUMBLING, state);
			if (!state) stateMask |= CreatureState::TUMBLING;
			row->getValue(CommandConfigManager::RALLIED, state);
			if (!state) stateMask |= CreatureState::RALLIED;
			row->getValue(CommandConfigManager::STUNNED, state);
			if (!state) stateMask |= CreatureState::STUNNED;
			row->getValue(CommandConfigManager::BLINDED, state);
			if (!state) stateMask |= CreatureState::BLINDED;
			row->getValue(CommandConfigManager::DIZZY, state);
			if (!state) stateMask |= CreatureState::DIZZY;
			row->getValue(CommandConfigManager::INTIMIDATED, state);
			if (!state) stateMask |= CreatureState::INTIMIDATED;
			row->getValue(CommandConfigManager::IMMOBILIZED, state);
			if (!state) stateMask |= CreatureState::IMMOBILIZED;
			row->getValue(CommandConfigManager::FROZEN, state);
			if (!state) stateMask |= CreatureState::FROZEN;
			row->getValue(CommandConfigManager::SWIMMING, state);
			if (!state) stateMask |= CreatureState::SWIMMING;
			row->getValue(CommandConfigManager::SITTINGONCHAIR, state);
			if (!state) stateMask |= CreatureState::SITTINGONCHAIR;
			row->getValue(CommandConfigManager::CRAFTING, state);
			if (!state) stateMask |= CreatureState::CRAFTING;
			row->getValue(CommandConfigManager::GLOWINGJEDI, state);
			if (!state) stateMask |= CreatureState::GLOWINGJEDI;
			row->getValue(CommandConfigManager::MASKSCENT, state);
			if (!state) stateMask |= CreatureState::MASKSCENT;
			row->getValue(CommandConfigManager::POISONED, state);
			if (!state) stateMask |= CreatureState::POISONED;
			row->getValue(CommandConfigManager::BLEEDING, state);
			if (!state) stateMask |= CreatureState::BLEEDING;
			row->getValue(CommandConfigManager::DISEASED, state);
			if (!state) stateMask |= CreatureState::DISEASED;
			row->getValue(CommandConfigManager::ONFIRE, state);
			if (!state) stateMask |= CreatureState::ONFIRE;
			row->getValue(CommandConfigManager::RIDINGMOUNT, state);
			if (!state) stateMask |= CreatureState::RIDINGMOUNT;
			row->getValue(CommandConfigManager::MOUNTEDCREATURE, state);
			if (!state) stateMask |= CreatureState::MOUNTEDCREATURE;
			row->getValue(CommandConfigManager::PILOTINGSHIP, state);
			if (!state) stateMask |= CreatureState::PILOTINGSHIP;
			row->getValue(CommandConfigManager::PILOTINGPOBSHIP, state);
			if (!state) stateMask |= CreatureState::PILOTINGPOBSHIP;
			row->getValue(CommandConfigManager::SHIPOPERATIONS, state);
			if (!state) stateMask |= CreatureState::SHIPOPERATIONS;
			row->getValue(CommandConfigManager::SHIPGUNNER, state);
			if (!state) stateMask |= CreatureState::SHIPGUNNER;
			row->getValue(CommandConfigManager::SHIPINTERIOR, state);
			if (!state) stateMask |= CreatureState::SHIPINTERIOR;

			slashCommand->setStateMask(stateMask);

			// add prohibited locomotions
			row->getValue(CommandConfigManager::STANDING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::STANDING);
			row->getValue(CommandConfigManager::SNEAKING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::SNEAKING);
			row->getValue(CommandConfigManager::WALKING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::WALKING);
			row->getValue(CommandConfigManager::RUNNING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::RUNNING);
			row->getValue(CommandConfigManager::KNEELING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::KNEELING);
			row->getValue(CommandConfigManager::CROUCHSNEAKING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CROUCHSNEAKING);
			row->getValue(CommandConfigManager::CROUCHWALKING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CROUCHWALKING);
			row->getValue(CommandConfigManager::PRONE, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::PRONE);
			row->getValue(CommandConfigManager::CRAWLING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CRAWLING);
			row->getValue(CommandConfigManager::CLIMBINGSTATIONARY, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CLIMBINGSTATIONARY);
			row->getValue(CommandConfigManager::CLIMBING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CLIMBING);
			row->getValue(CommandConfigManager::HOVERING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::HOVERING);
			row->getValue(CommandConfigManager::FLYING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::FLYING);
			row->getValue(CommandConfigManager::LYINGDOWN, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::LYINGDOWN);
			row->getValue(CommandConfigManager::SITTING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::SITTING);
			row->getValue(CommandConfigManager::SKILLANIMATING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::SKILLANIMATING);
			row->getValue(CommandConfigManager::DRIVINGVEHICLE, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::DRIVINGVEHICLE);
			row->getValue(CommandConfigManager::RIDINGCREATURE, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::RIDINGCREATURE);
			row->getValue(CommandConfigManager::KNOCKEDDOWN, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::KNOCKEDDOWN);
			row->getValue(CommandConfigManager::INCAPACITATED, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::INCAPACITATED);
			row->getValue(CommandConfigManager::DEAD, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::DEAD);
			row->getValue(CommandConfigManager::BLOCKING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::BLOCKING);

			uint32 group;
			row->getValue(CommandConfigManager::COMMANDGROUP, group);

			slashCommand->setCommandGroup(group);

			String coolDownGroup;
			row->getValue(CommandConfigManager::COOLDOWNGROUP, coolDownGroup);

			slashCommand->setCoolDownGroup(coolDownGroup);

			float warmUpTime;
			row->getValue(CommandConfigManager::WARMUPTIME, warmUpTime);

			slashCommand->setWarmup(warmUpTime);

			float executeTime;
			row->getValue(CommandConfigManager::EXECUTETIME, executeTime);

			slashCommand->setExecuteTime(executeTime);

			float coolDownTime;
			row->getValue(CommandConfigManager::COOLDOWNTIME, coolDownTime);

			slashCommand->setCooldown(coolDownTime);

			num++;
		}
	}

	info("Loaded " + String::valueOf(num) + " commands from " + filename + ".");
}

QueueCommand* CommandConfigManager::createCommand(const String& name) {
	QueueCommand* command = NULL;

	command = commandFactory.createCommand(name, name, server);

	if (command == NULL)
		return command;

	slashCommands->put(command);

	info("created command " + name);

	return command;
}

void CommandConfigManager::registerSpecialCommands(CommandList* sCommands) {
	slashCommands = sCommands;
	QueueCommand* admin = new AdminCommand("admin", server);
	slashCommands->put(admin);
	// Fri Oct  7 17:09:26 PDT 2011 - Karl Bunch <karlbunch@karlbunch.com>
	// Turns out this isn't in the base datatables/command/command_tables_shared.iff file
	// Meanwhile the client sends this to the server as part of the /logout command sequence
	QueueCommand* slashCommand = createCommand(String("logout").toLowerCase());

	if (slashCommand == NULL) {
		error("Could not create command /logout");
	}

	createCommand(String("mildPoison").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("strongPoison").toLowerCase())->setCommandGroup(0xe1c9a54a);

	createCommand(String("mediumPoison").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("mediumDisease").toLowerCase())->setCommandGroup(0xe1c9a54a);

	createCommand(String("mildDisease").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("strongDisease").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("turretFire").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("turretFireManual").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("minefieldAttack").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("creatureRangedAttack").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("defaultDroidAttack").toLowerCase())->setCommandGroup(0xe1c9a54a);

	//Pet commands
	createCommand(String("petAttack").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petEmote").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petFeed").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petFollow").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petGroup").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petRecharge").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petRechargeOther").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petRecover").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petSpecialAttack").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petStay").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petStore").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petTransfer").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petTrick").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petRepair").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petThrow").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petHarvest").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petPatrol").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petClearPatrolPoints").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petGetPatrolPoint").toLowerCase())->setCommandGroup(0xe1c9a54a);
}

void CommandConfigManager::registerFunctions() {
	//lua generic
	lua_register(getLuaState(), "RunSlashCommandsFile", runSlashCommandsFile);
	lua_register(getLuaState(), "AddCommand", addCommand);
	lua_register(getLuaState(), "hashCode", hashCode);
}

void CommandConfigManager::registerGlobals() {
	//states
	setGlobalLong("INVALID_STATE", CreatureState::INVALID);
	setGlobalLong("COVER_STATE", CreatureState::COVER);
	setGlobalLong("COMBAT_STATE", CreatureState::COMBAT);
	setGlobalLong("PEACE_STATE", CreatureState::PEACE);
	setGlobalLong("AIMING_STATE", CreatureState::AIMING);
	setGlobalLong("ALERT_STATE", CreatureState::ALERT);
	setGlobalLong("BERSERK_STATE", CreatureState::BERSERK);
	setGlobalLong("FEIGNDEATH_STATE", CreatureState::FEIGNDEATH);
	setGlobalLong("COMBATATTITUDEEVASIVE_STATE", CreatureState::COMBATATTITUDEEVASIVE);
	setGlobalLong("COMBATATTITUDENORMAL_STATE", CreatureState::COMBATATTITUDENORMAL);
	setGlobalLong("COMBATATTITUDEAGGRESSIVE_STATE", CreatureState::COMBATATTITUDEAGGRESSIVE);
	setGlobalLong("TUMBLING_STATE", CreatureState::TUMBLING);
	setGlobalLong("RALLIED_STATE", CreatureState::RALLIED);
	setGlobalLong("STUNNED_STATE", CreatureState::STUNNED);
	setGlobalLong("BLINDED_STATE", CreatureState::BLINDED);
	setGlobalLong("DIZZY_STATE", CreatureState::DIZZY);
	setGlobalLong("INTIMIDATED_STATE", CreatureState::INTIMIDATED);
	setGlobalLong("IMMOBILIZED_STATE", CreatureState::IMMOBILIZED);
	setGlobalLong("FROZEN_STATE", CreatureState::FROZEN);
	setGlobalLong("SWIMMING_STATE", CreatureState::SWIMMING);
	setGlobalLong("SITTINGONCHAIR_STATE", CreatureState::SITTINGONCHAIR);
	setGlobalLong("CRAFTING_STATE", CreatureState::CRAFTING);
	setGlobalLong("GLOWINGJEDI_STATE", CreatureState::GLOWINGJEDI);
	setGlobalLong("MASKSCENT_STATE", CreatureState::MASKSCENT);
	setGlobalLong("POISONED", CreatureState::POISONED);
	setGlobalLong("BLEEDING", CreatureState::BLEEDING);
	setGlobalLong("DISEASED", CreatureState::DISEASED);
	setGlobalLong("ONFIRE", CreatureState::ONFIRE);
	setGlobalLong("RIDINGMOUNT_STATE", CreatureState::RIDINGMOUNT);
	setGlobalLong("MOUNTEDCREATURE_STATE", CreatureState::MOUNTEDCREATURE);
	setGlobalLong("PILOTINGSHIP_STATE", CreatureState::PILOTINGSHIP);
	setGlobalLong("PILOTINGPOBSHIP_STATE", CreatureState::PILOTINGPOBSHIP);
	setGlobalLong("SHIPOPERATIONS_STATE", CreatureState::SHIPOPERATIONS);
	setGlobalLong("SHIPGUNNER_STATE", CreatureState::SHIPGUNNER);
	setGlobalLong("SHIPINTERIOR_STATE", CreatureState::SHIPINTERIOR);

	// locomotion
	setGlobalInt("INVALID_LOCOMOTION", CreatureLocomotion::INVALID);
	setGlobalInt("STANDING_LOCOMOTION", CreatureLocomotion::STANDING);
	setGlobalInt("SNEAKING_LOCOMOTION", CreatureLocomotion::SNEAKING);
	setGlobalInt("WALKING_LOCOMOTION", CreatureLocomotion::WALKING);
	setGlobalInt("RUNNING_LOCOMOTION", CreatureLocomotion::RUNNING);
	setGlobalInt("KNEELING_LOCOMOTION", CreatureLocomotion::KNEELING);
	setGlobalInt("CROUCHSNEAKING_LOCOMOTION", CreatureLocomotion::CROUCHSNEAKING);
	setGlobalInt("CROUCHWALKING_LOCOMOTION", CreatureLocomotion::CROUCHWALKING);
	setGlobalInt("PRONE_LOCOMOTION", CreatureLocomotion::PRONE);
	setGlobalInt("CRAWLING_LOCOMOTION", CreatureLocomotion::CRAWLING);
	setGlobalInt("CLIMBINGSTATIONARY_LOCOMOTION", CreatureLocomotion::CLIMBINGSTATIONARY);
	setGlobalInt("CLIMBING_LOCOMOTION", CreatureLocomotion::CLIMBING);
	setGlobalInt("HOVERING_LOCOMOTION", CreatureLocomotion::HOVERING);
	setGlobalInt("FLYING_LOCOMOTION", CreatureLocomotion::FLYING);
	setGlobalInt("LYINGDOWN_LOCOMOTION", CreatureLocomotion::LYINGDOWN);
	setGlobalInt("SITTING_LOCOMOTION", CreatureLocomotion::SITTING);
	setGlobalInt("SKILLANIMATING_LOCOMOTION", CreatureLocomotion::SKILLANIMATING);
	setGlobalInt("DRIVINGVEHICLE_LOCOMOTION", CreatureLocomotion::DRIVINGVEHICLE);
	setGlobalInt("RIDINGCREATURE_LOCOMOTION", CreatureLocomotion::RIDINGCREATURE);
	setGlobalInt("KNOCKEDDOWN_LOCOMOTION", CreatureLocomotion::KNOCKEDDOWN);
	setGlobalInt("INCAPACITATED_LOCOMOTION", CreatureLocomotion::INCAPACITATED);
	setGlobalInt("DEAD_LOCOMOTION", CreatureLocomotion::DEAD);
	setGlobalInt("BLOCKING_LOCOMOTION", CreatureLocomotion::BLOCKING);

	// attributes
	setGlobalInt("HEALTH_ATTRIBUTE", CombatManager::HEALTH);
	setGlobalInt("ACTION_ATTRIBUTE", CombatManager::ACTION);
	setGlobalInt("MIND_ATTRIBUTE", CombatManager::MIND);
	setGlobalInt("RANDOM_ATTRIBUTE", CombatManager::RANDOM);

	setGlobalInt("HEALTH", CreatureAttribute::HEALTH);
	setGlobalInt("ACTION", CreatureAttribute::ACTION);
	setGlobalInt("MIND", CreatureAttribute::MIND);

	// weapons
	// TODO: make valid weapons into a mask and check all combat commands
	setGlobalInt("MELEEWEAPON_WEAPON", CombatManager::MELEEWEAPON);
	setGlobalInt("RANGEDWEAPON_WEAPON", CombatManager::RANGEDWEAPON);
	setGlobalInt("THROWNWEAPON_WEAPON", CombatManager::THROWNWEAPON);
	setGlobalInt("HEAVYWEAPON_WEAPON", CombatManager::HEAVYWEAPON);
	setGlobalInt("MINE_WEAPON", CombatManager::MINEWEAPON);
	setGlobalInt("SPECIALHEAVYWEAPON_WEAPON", CombatManager::SPECIALHEAVYWEAPON);
	setGlobalInt("ONEHANDMELEEWEAPON_WEAPON", CombatManager::ONEHANDMELEEWEAPON);
	setGlobalInt("TWOHANDMELEEWEAPON_WEAPON", CombatManager::TWOHANDMELEEWEAPON);
	setGlobalInt("POLEARM_WEAPON", CombatManager::POLEARMWEAPON);
	setGlobalInt("PISTOL_WEAPON", CombatManager::PISTOLWEAPON);
	setGlobalInt("CARBINE_WEAPON", CombatManager::CARBINEWEAPON);
	setGlobalInt("RIFLE_WEAPON", CombatManager::RIFLEWEAPON);
	setGlobalInt("GRENADE_WEAPON", CombatManager::GRENADEWEAPON);
	setGlobalInt("LIGHTNINGRIFLE_WEAPON", CombatManager::LIGHTNINGRIFLEWEAPON);

	// effects
	setGlobalInt("INVALID_EFFECT", CommandEffect::INVALID);
	setGlobalInt("BLIND_EFFECT", CommandEffect::BLIND);
	setGlobalInt("DIZZY_EFFECT", CommandEffect::DIZZY);
	setGlobalInt("INTIMIDATE_EFFECT", CommandEffect::INTIMIDATE);
	setGlobalInt("STUN_EFFECT", CommandEffect::STUN);
	setGlobalInt("KNOCKDOWN_EFFECT", CommandEffect::KNOCKDOWN);
	setGlobalInt("POSTUREUP_EFFECT", CommandEffect::POSTUREUP);
	setGlobalInt("POSTUREDOWN_EFFECT", CommandEffect::POSTUREDOWN);
	setGlobalInt("NEXTATTACKDELAY_EFFECT", CommandEffect::NEXTATTACKDELAY);
	setGlobalInt("HEALTHDEGRADE_EFFECT", CommandEffect::HEALTHDEGRADE);
	setGlobalInt("ACTIONDEGRADE_EFFECT", CommandEffect::ACTIONDEGRADE);
	setGlobalInt("MINDDEGRADE_EFFECT", CommandEffect::MINDDEGRADE);

	// trails
	setGlobalInt("NOTRAIL", CombatManager::NOTRAIL);
	setGlobalInt("LEFTFOOTTRAIL", CombatManager::LEFTFOOTTRAIL);
	setGlobalInt("RIGHTFOOTTRAIL", CombatManager::RIGHTFOOTTRAIL);
	setGlobalInt("LEFTHANDTRAIL", CombatManager::LEFTHANDTRAIL);
	setGlobalInt("RIGHTHANDTRAIL", CombatManager::RIGHTHANDTRAIL);
	setGlobalInt("WEAPONTRAIL", CombatManager::WEAPONTRAIL);
	setGlobalInt("DEFAULTTRAIL", CombatManager::DEFAULTTRAIL);

	// attack types
	setGlobalInt("WEAPONATTACK", CombatManager::WEAPONATTACK);
	setGlobalInt("FORCEATTACK", CombatManager::FORCEATTACK);
}

int CommandConfigManager::runSlashCommandsFile(lua_State* L) {
	String filename;

	filename = getStringParameter(L);

	bool res = runFile("scripts/commands/" + filename, L);

	if (!res)
		ERROR_CODE = GENERAL_ERROR;

	return 0;
}

void CommandConfigManager::parseOptions(LuaObject &slashcommand, QueueCommand* command) {
	lua_State* L = slashcommand.getLuaState();

	if (!slashcommand.isValidTable())
		return;

	lua_pushnil(L);
	while (lua_next(L, -2) != 0) {
		// 'key' is at index -2 and 'value' at index -1
		if (lua_type(L, -2) == LUA_TSTRING) {
			String varName = lua_tolstring(L, -2, 0);
			parseVariableData(varName, slashcommand, command);
		} else
			lua_pop(L, 1);
	}
}

void CommandConfigManager::parseVariableData(String varName, LuaObject &command, QueueCommand* slashCommand) {
	lua_State* L = command.getLuaState();

	// overwrite data from command_table
	if (varName == "name") // just ignore name, it's only used to grab the object from the table
		command.pop();
	else if (varName == "invalidStateMask")
		slashCommand->setStateMask(Lua::getUnsignedLongParameter(L));
	else if (varName == "invalidLocomotions")
		slashCommand->setInvalidLocomotions(Lua::getStringParameter(L));
	else if (varName == "targetType")
		slashCommand->setTargetType(Lua::getIntParameter(L));
	else if (varName == "disabled") {
		slashCommand->setDisabled((bool)lua_toboolean(L, -1));
		command.pop();
	} else if (varName == "maxRangeToTarget")
		slashCommand->setMaxRange(Lua::getIntParameter(L));
	else if (varName == "addToCombatQueue") {
		slashCommand->setAddToCombatQueue((bool)lua_toboolean(L, -1));
		command.pop();
	} else if (varName == "characterAbility")
		slashCommand->setCharacterAbility(Lua::getStringParameter(L));
	else if (varName == "defaultPriority")
		slashCommand->setDefaultPriority(Lua::getStringParameter(L));
	else if (varName == "defaultTime")
		slashCommand->setDefaultTime(Lua::getFloatParameter(L));
	else if (varName == "skillMods") {
		LuaObject skillMods(L);

		for (int i = 1; i <= skillMods.getTableSize(); ++i) {
			LuaObject skillEntry = skillMods.getObjectAt(i);
			slashCommand->addSkillMod(skillEntry.getStringAt(1), skillEntry.getIntAt(2));
			skillEntry.pop();
		}
		skillMods.pop();

	} else if (slashCommand->isCombatCommand()) { // define combat variables (for combat commands)
		CombatQueueCommand* combatCommand = cast<CombatQueueCommand*>(slashCommand);
		if (varName == "attackType")
			combatCommand->setAttackType(Lua::getIntParameter(L));
		else if (varName == "damageMultiplier")
			combatCommand->setDamageMultiplier(Lua::getFloatParameter(L));
		else if (varName == "accuracyBonus")
			combatCommand->setAccuracyBonus(Lua::getIntParameter(L));
		else if (varName == "speedMultiplier")
			combatCommand->setSpeedMultiplier(Lua::getFloatParameter(L));
		else if (varName == "damage")
			combatCommand->setDamage(Lua::getFloatParameter(L));
		else if (varName == "speed")
			combatCommand->setSpeed(Lua::getFloatParameter(L));
		else if (varName == "poolsToDamage")
			combatCommand->setPoolsToDamage(Lua::getIntParameter(L));
		else if (varName == "healthCostMultiplier")
			combatCommand->setHealthCostMultiplier(Lua::getFloatParameter(L));
		else if (varName == "actionCostMultiplier")
			combatCommand->setActionCostMultiplier(Lua::getFloatParameter(L));
		else if (varName == "mindCostMultiplier")
			combatCommand->setMindCostMultiplier(Lua::getFloatParameter(L));
		else if (varName == "forceCostMultiplier")
			combatCommand->setForceCostMultiplier(Lua::getFloatParameter(L));
		else if (varName == "forceCost")
			combatCommand->setForceCost(Lua::getFloatParameter(L));
		else if (varName == "range")
			combatCommand->setRange(Lua::getIntParameter(L));
		else if (varName == "accuracySkillMod")
			combatCommand->setAccuracySkillMod(Lua::getStringParameter(L));
		else if (varName == "areaAction") {
			combatCommand->setAreaAction((bool)lua_toboolean(L, -1));
			command.pop();
		} else if (varName == "coneAction") {
			combatCommand->setConeAction((bool)lua_toboolean(L, -1));
			command.pop();
		} else if (varName == "coneAngle")
			combatCommand->setConeAngle(Lua::getIntParameter(L));
		else if (varName == "areaRange")
			combatCommand->setAreaRange(Lua::getIntParameter(L));
		else if (varName == "combatSpam")
			combatCommand->setCombatSpam(Lua::getStringParameter(L));
		else if (varName == "animationCRC")
			combatCommand->setAnimationCRC(Lua::getUnsignedIntParameter(L));
		else if (varName == "effectString")
			combatCommand->setEffectString(Lua::getStringParameter(L));
		else if (varName == "trails")
			combatCommand->setTrails(Lua::getIntParameter(L));
		else if (varName == "stateEffects") {
			LuaObject states(L);

			for (int i = 1; i <= states.getTableSize(); ++i) {
				lua_rawgeti(L, -1, i);
				LuaObject state(L);
				combatCommand->addStateEffect(StateEffect(state));
				state.pop();
			}

			states.pop();
		} else if (varName == "dotEffects") {
			LuaObject dots(L);

			for (int i = 1; i <= dots.getTableSize(); ++i) {
				lua_rawgeti(L, -1, i);
				LuaObject dot(L);
				combatCommand->addDotEffect(DotEffect(dot));
				//System::out << "count " << combatCommand->getDotEffects()->size()<< endl;
				dot.pop();
			}

			dots.pop();
		} else if (combatCommand->isSquadLeaderCommand()) {
			SquadLeaderCommand* slCommand = cast<SquadLeaderCommand*>(combatCommand);
			if (varName == "action")
				slCommand->setAction(Lua::getStringParameter(L));
			else {
				Logger::console.error("unknown variable " + varName + " in squadleader command " + slashCommand->getQueueCommandName());
				command.pop();
			}

		} else {
			Logger::console.error("unknown variable " + varName + " in combat command " + slashCommand->getQueueCommandName());
			command.pop();
		}

	}else {
		Logger::console.error("unknown variable " + varName + " in command " + slashCommand->getQueueCommandName());
		command.pop();
	}
}

void CommandConfigManager::parseAlternativeNames(String& alternativeNames, QueueCommand* slashCommand) {
	StringTokenizer tokenizer(alternativeNames);
	tokenizer.setDelimeter(",");

	String token = "";
	while (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(token);

		slashCommands->put(token, slashCommand);
	}
}

int CommandConfigManager::hashCode(lua_State* L) {
	const char* anim = lua_tostring(L, -1);

	lua_pushnumber(L, String(anim).hashCode());

	return 1;
}

int CommandConfigManager::addCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	// get object from map, then overwrite/fill in variables
	String name = slashcommand.getStringField("name");
	QueueCommand* command = slashCommands->getSlashCommand(name);
	if (command == NULL)
		return 0;

	parseOptions(slashcommand, command);

	return 1;
}

void CommandConfigManager::registerCommands() {
	/*
	commandFactory.registerCommand<AbandonQuestCommand>(String("AbandonQuest").toLowerCase());
	commandFactory.registerCommand<AborthyperspaceCommand>(String("Aborthyperspace").toLowerCase());
	commandFactory.registerCommand<ActivateCloneCommand>(String("ActivateClone").toLowerCase());
	commandFactory.registerCommand<ActivateInstanceCommand>(String("ActivateInstance").toLowerCase());
	commandFactory.registerCommand<ActivateQuestCommand>(String("ActivateQuest").toLowerCase());
	commandFactory.registerCommand<AddAllowedPlayerCommand>(String("AddAllowedPlayer").toLowerCase());
	commandFactory.registerCommand<AddBannedPlayerCommand>(String("AddBannedPlayer").toLowerCase());
	commandFactory.registerCommand<AddFriendCommand>(String("AddFriend").toLowerCase());
	commandFactory.registerCommand<AddIgnoreCommand>(String("AddIgnore").toLowerCase());
	commandFactory.registerCommand<AddMapLocationCommand>(String("AddMapLocation").toLowerCase());
	commandFactory.registerCommand<AddPowerCommand>(String("AddPower").toLowerCase());
	commandFactory.registerCommand<AdjustLotCountCommand>(String("AdjustLotCount").toLowerCase());
	commandFactory.registerCommand<AdrenalBoostCommand>(String("AdrenalBoost").toLowerCase());
	commandFactory.registerCommand<AiIgnoreCommand>(String("AiIgnore").toLowerCase());
	commandFactory.registerCommand<AimCommand>(String("Aim").toLowerCase());
	commandFactory.registerCommand<AimedShotCommand>(String("AimedShot").toLowerCase());
	commandFactory.registerCommand<AlertCommand>(String("Alert").toLowerCase());
	commandFactory.registerCommand<AnonCommand>(String("Anon").toLowerCase());
	commandFactory.registerCommand<ApplyPowerupCommand>(String("ApplyPowerup").toLowerCase());
	commandFactory.registerCommand<AreaTauntCommand>(String("AreaTaunt").toLowerCase());
	commandFactory.registerCommand<AreatrackCommand>(String("Areatrack").toLowerCase());
	commandFactory.registerCommand<ArmorBreakCommand>(String("ArmorBreak").toLowerCase());
	commandFactory.registerCommand<AssignDroidCommand>(String("AssignDroid").toLowerCase());
	commandFactory.registerCommand<AssistCommand>(String("Assist").toLowerCase());
	commandFactory.registerCommand<AssociateDroidControlDeviceWithShipCommand>(String("AssociateDroidControlDeviceWithShip").toLowerCase());
	commandFactory.registerCommand<AttackCommand>(String("Attack").toLowerCase());
	commandFactory.registerCommand<AuctionAcceptCommand>(String("AuctionAccept").toLowerCase());
	commandFactory.registerCommand<AuctionBidCommand>(String("AuctionBid").toLowerCase());
	commandFactory.registerCommand<AuctionCancelCommand>(String("AuctionCancel").toLowerCase());
	commandFactory.registerCommand<AuctionCommand>(String("Auction").toLowerCase());
	commandFactory.registerCommand<AuctionCreateCommand>(String("AuctionCreate").toLowerCase());
	commandFactory.registerCommand<AuctionQueryCommand>(String("AuctionQuery").toLowerCase());
	commandFactory.registerCommand<AuctionRetrieveCommand>(String("AuctionRetrieve").toLowerCase());
	commandFactory.registerCommand<AuctionsayCommand>(String("Auctionsay").toLowerCase());
	commandFactory.registerCommand<AvoidIncapacitationCommand>(String("AvoidIncapacitation").toLowerCase());
	commandFactory.registerCommand<BactaInfusionCommand>(String("BactaInfusion").toLowerCase());
	commandFactory.registerCommand<BactaJabCommand>(String("BactaJab").toLowerCase());
	commandFactory.registerCommand<BactaShotCommand>(String("BactaShot").toLowerCase());
	commandFactory.registerCommand<BactaSprayCommand>(String("BactaSpray").toLowerCase());
	commandFactory.registerCommand<BactaTossCommand>(String("BactaToss").toLowerCase());
	commandFactory.registerCommand<BandFlourishCommand>(String("BandFlourish").toLowerCase());
	commandFactory.registerCommand<BandageCommand>(String("Bandage").toLowerCase());
	commandFactory.registerCommand<BattlefieldStatusCommand>(String("BattlefieldStatus").toLowerCase());
	commandFactory.registerCommand<BerserkCommand>(String("Berserk").toLowerCase());
	commandFactory.registerCommand<BetCommand>(String("Bet").toLowerCase());
	commandFactory.registerCommand<BindingStrikeCommand>(String("BindingStrike").toLowerCase());
	commandFactory.registerCommand<BlazeOfGloryCommand>(String("BlazeOfGlory").toLowerCase());
	commandFactory.registerCommand<BleedAttackCommand>(String("BleedAttack").toLowerCase());
	commandFactory.registerCommand<BlindAttackCommand>(String("BlindAttack").toLowerCase());
	commandFactory.registerCommand<BlindRecoveryCommand>(String("BlindRecovery").toLowerCase());
	commandFactory.registerCommand<BoardShuttleCommand>(String("BoardShuttle").toLowerCase());
	commandFactory.registerCommand<BodyHitCommand>(String("BodyHit").toLowerCase());
	commandFactory.registerCommand<BodyShotCommand>(String("BodyShot").toLowerCase());
	commandFactory.registerCommand<BoosterOffCommand>(String("BoosterOff").toLowerCase());
	commandFactory.registerCommand<BoosterOnCommand>(String("BoosterOn").toLowerCase());
	commandFactory.registerCommand<BoostmoraleCommand>(String("Boostmorale").toLowerCase());
	commandFactory.registerCommand<BroadcastAreaCommand>(String("BroadcastArea").toLowerCase());
	commandFactory.registerCommand<BroadcastCommand>(String("Broadcast").toLowerCase());
	commandFactory.registerCommand<BroadcastGalaxyCommand>(String("BroadcastGalaxy").toLowerCase());
	commandFactory.registerCommand<BroadcastPlanetCommand>(String("BroadcastPlanet").toLowerCase());
	commandFactory.registerCommand<Bstrike1Command>(String("Bstrike1").toLowerCase());
	commandFactory.registerCommand<Bstrike2Command>(String("Bstrike2").toLowerCase());
	commandFactory.registerCommand<Bstrike3Command>(String("Bstrike3").toLowerCase());
	commandFactory.registerCommand<BurstRunCommand>(String("BurstRun").toLowerCase());
	commandFactory.registerCommand<BurstShotCommand>(String("BurstShot").toLowerCase());
	commandFactory.registerCommand<CallToArmsCommand>(String("CallToArms").toLowerCase());
	commandFactory.registerCommand<CalledShotCommand>(String("CalledShot").toLowerCase());
	commandFactory.registerCommand<CancelCraftingSessionCommand>(String("CancelCraftingSession").toLowerCase());
	commandFactory.registerCommand<CenterOfBeingCommand>(String("CenterOfBeing").toLowerCase());
	commandFactory.registerCommand<CenterStageCommand>(String("CenterStage").toLowerCase());
	commandFactory.registerCommand<ChangeBandMusicCommand>(String("ChangeBandMusic").toLowerCase());
	commandFactory.registerCommand<ChangeDanceCommand>(String("ChangeDance").toLowerCase());
	commandFactory.registerCommand<ChangeMusicCommand>(String("ChangeMusic").toLowerCase());
	commandFactory.registerCommand<ChannelForceCommand>(String("ChannelForce").toLowerCase());
	commandFactory.registerCommand<ChargeCommand>(String("Charge").toLowerCase());
	commandFactory.registerCommand<ChargeShotCommand>(String("ChargeShot").toLowerCase());
	commandFactory.registerCommand<CheckForceStatusCommand>(String("CheckForceStatus").toLowerCase());
	commandFactory.registerCommand<CityInfoCommand>(String("CityInfo").toLowerCase());
	commandFactory.registerCommand<CitybanCommand>(String("Cityban").toLowerCase());
	commandFactory.registerCommand<CitypardonCommand>(String("Citypardon").toLowerCase());
	commandFactory.registerCommand<ClaimVeteranRewardCommand>(String("ClaimVeteranReward").toLowerCase());
	commandFactory.registerCommand<ClearCompletedQuestCommand>(String("ClearCompletedQuest").toLowerCase());
	commandFactory.registerCommand<ClearQueueCommand>(String("ClearQueue").toLowerCase());
	commandFactory.registerCommand<ClearVeteranRewardCommand>(String("ClearVeteranReward").toLowerCase());
	commandFactory.registerCommand<ClientQualifiedForSkillCommand>(String("ClientQualifiedForSkill").toLowerCase());
	commandFactory.registerCommand<CloakOfLavaCommand>(String("CloakOfLava").toLowerCase());
	commandFactory.registerCommand<CloneCommand>(String("Clone").toLowerCase());
	commandFactory.registerCommand<CloseContainerCommand>(String("CloseContainer").toLowerCase());
	commandFactory.registerCommand<CloseLotteryContainerCommand>(String("CloseLotteryContainer").toLowerCase());
	commandFactory.registerCommand<CloseWingsCommand>(String("CloseWings").toLowerCase());
	commandFactory.registerCommand<CobCommand>(String("Cob").toLowerCase());
	commandFactory.registerCommand<ColorSwirlCommand>(String("ColorSwirl").toLowerCase());
	commandFactory.registerCommand<ColorlightsCommand>(String("Colorlights").toLowerCase());
	commandFactory.registerCommand<CombatCommand>(String("Combat").toLowerCase());
	commandFactory.registerCommand<CombatEscapeCommand>(String("CombatEscape").toLowerCase());
	commandFactory.registerCommand<CombatFeintCommand>(String("CombatFeint").toLowerCase());
	commandFactory.registerCommand<CombatModeCheckCommand>(String("CombatModeCheck").toLowerCase());
	commandFactory.registerCommand<CombatSpamCommand>(String("CombatSpam").toLowerCase());
	commandFactory.registerCommand<CombatTargetCommand>(String("CombatTarget").toLowerCase());
	commandFactory.registerCommand<ComboAttackCommand>(String("ComboAttack").toLowerCase());
	commandFactory.registerCommand<CompleteQuestCommand>(String("CompleteQuest").toLowerCase());
	commandFactory.registerCommand<ConcealCommand>(String("Conceal").toLowerCase());
	commandFactory.registerCommand<ConcealShotCommand>(String("ConcealShot").toLowerCase());
	commandFactory.registerCommand<ConcussionShotCommand>(String("ConcussionShot").toLowerCase());
	commandFactory.registerCommand<ConfusionShotCommand>(String("ConfusionShot").toLowerCase());
	commandFactory.registerCommand<ConsentCommand>(String("Consent").toLowerCase());
	commandFactory.registerCommand<CorpseCommand>(String("Corpse").toLowerCase());
	commandFactory.registerCommand<CounterAttackCommand>(String("CounterAttack").toLowerCase());
	commandFactory.registerCommand<CountertoxinCommand>(String("Countertoxin").toLowerCase());
	commandFactory.registerCommand<CountertoxinSprayCommand>(String("CountertoxinSpray").toLowerCase());
	commandFactory.registerCommand<CoupDeGraceCommand>(String("CoupDeGrace").toLowerCase());
	commandFactory.registerCommand<CoverCommand>(String("Cover").toLowerCase());
	commandFactory.registerCommand<CoverchargeCommand>(String("Covercharge").toLowerCase());
	commandFactory.registerCommand<CraftCommand>(String("Craft").toLowerCase());
	commandFactory.registerCommand<CreateCreatureCommand>(String("CreateCreature").toLowerCase());
	commandFactory.registerCommand<CreateManfSchematicCommand>(String("CreateManfSchematic").toLowerCase());
	commandFactory.registerCommand<CreateMissionElementCommand>(String("CreateMissionElement").toLowerCase());
	commandFactory.registerCommand<CreateNPCCommand>(String("CreateNPC").toLowerCase());
	commandFactory.registerCommand<CreatePrototypeCommand>(String("CreatePrototype").toLowerCase());
	commandFactory.registerCommand<CreateSpawningElementCommand>(String("CreateSpawningElement").toLowerCase());
	commandFactory.registerCommand<CreateSpawningElementWithDifficultyCommand>(String("CreateSpawningElementWithDifficulty").toLowerCase());
	commandFactory.registerCommand<CreateStaticItemCommand>(String("CreateStaticItem").toLowerCase());
	commandFactory.registerCommand<CreateVendorCommand>(String("CreateVendor").toLowerCase());
	commandFactory.registerCommand<CreatureAreaAttackCommand>(String("CreatureAreaAttack").toLowerCase());
	commandFactory.registerCommand<CreatureAreaBleedingCommand>(String("CreatureAreaBleeding").toLowerCase());
	commandFactory.registerCommand<CreatureAreaComboCommand>(String("CreatureAreaCombo").toLowerCase());
	commandFactory.registerCommand<CreatureAreaDiseaseCommand>(String("CreatureAreaDisease").toLowerCase());
	commandFactory.registerCommand<CreatureAreaKnockdownCommand>(String("CreatureAreaKnockdown").toLowerCase());
	commandFactory.registerCommand<CreatureAreaPoisonCommand>(String("CreatureAreaPoison").toLowerCase());
	commandFactory.registerCommand<CreatureBlindAttackCommand>(String("CreatureBlindAttack").toLowerCase());
	commandFactory.registerCommand<CreatureDizzyAttackCommand>(String("CreatureDizzyAttack").toLowerCase());
	commandFactory.registerCommand<CreatureIntimidationAttackCommand>(String("CreatureIntimidationAttack").toLowerCase());
	commandFactory.registerCommand<CreatureKnockdownAttackCommand>(String("CreatureKnockdownAttack").toLowerCase());
	commandFactory.registerCommand<CreatureMeleeAttackCommand>(String("CreatureMeleeAttack").toLowerCase());
	commandFactory.registerCommand<CreaturePostureDownAttackCommand>(String("CreaturePostureDownAttack").toLowerCase());
	commandFactory.registerCommand<CreaturePostureUpAttackCommand>(String("CreaturePostureUpAttack").toLowerCase());
	commandFactory.registerCommand<CreatureRangedAttackCommand>(String("CreatureRangedAttack").toLowerCase());
	commandFactory.registerCommand<CreatureStunAttackCommand>(String("CreatureStunAttack").toLowerCase());
	commandFactory.registerCommand<CreditsCommand>(String("Credits").toLowerCase());
	commandFactory.registerCommand<CrippleAttackCommand>(String("CrippleAttack").toLowerCase());
	commandFactory.registerCommand<CripplingShotCommand>(String("CripplingShot").toLowerCase());
	commandFactory.registerCommand<CriticalShotCommand>(String("CriticalShot").toLowerCase());
	commandFactory.registerCommand<CriticalStrikeCommand>(String("CriticalStrike").toLowerCase());
	commandFactory.registerCommand<CsAppendCommentCommand>(String("CsAppendComment").toLowerCase());
	commandFactory.registerCommand<CsCancelTicketCommand>(String("CsCancelTicket").toLowerCase());
	commandFactory.registerCommand<CsConnectPlayerCommand>(String("CsConnectPlayer").toLowerCase());
	commandFactory.registerCommand<CsCreateTicketCommand>(String("CsCreateTicket").toLowerCase());
	commandFactory.registerCommand<CsDisconnectPlayerCommand>(String("CsDisconnectPlayer").toLowerCase());
	commandFactory.registerCommand<CsGetArticleCommand>(String("CsGetArticle").toLowerCase());
	commandFactory.registerCommand<CsGetCommentsCommand>(String("CsGetComments").toLowerCase());
	commandFactory.registerCommand<CsGetTicketsCommand>(String("CsGetTickets").toLowerCase());
	commandFactory.registerCommand<CsRequestCategoriesCommand>(String("CsRequestCategories").toLowerCase());
	commandFactory.registerCommand<CsSearchKnowledgeBaseCommand>(String("CsSearchKnowledgeBase").toLowerCase());
	commandFactory.registerCommand<CuiConsentResponseCommand>(String("CuiConsentResponse").toLowerCase());
	commandFactory.registerCommand<CureDiseaseCommand>(String("CureDisease").toLowerCase());
	commandFactory.registerCommand<CurePackCommand>(String("CurePack").toLowerCase());
	commandFactory.registerCommand<CurePoisonCommand>(String("CurePoison").toLowerCase());
	commandFactory.registerCommand<CustomizeDroidCommand>(String("CustomizeDroid").toLowerCase());
	commandFactory.registerCommand<CustomizeVehicleCommand>(String("CustomizeVehicle").toLowerCase());
	commandFactory.registerCommand<CyborgBurstRunCommand>(String("CyborgBurstRun").toLowerCase());
	commandFactory.registerCommand<CyborgCriticalSnipeCommand>(String("CyborgCriticalSnipe").toLowerCase());
	commandFactory.registerCommand<CyborgKickDownCommand>(String("CyborgKickDown").toLowerCase());
	commandFactory.registerCommand<CyborgLightningCommand>(String("CyborgLightning").toLowerCase());
	commandFactory.registerCommand<CyborgReviveCommand>(String("CyborgRevive").toLowerCase());
	commandFactory.registerCommand<CyborgStrengthBuffCommand>(String("CyborgStrengthBuff").toLowerCase());
	commandFactory.registerCommand<CyborgSureShotCommand>(String("CyborgSureShot").toLowerCase());
	commandFactory.registerCommand<DatabaseCommand>(String("Database").toLowerCase());
	commandFactory.registerCommand<DazzleCommand>(String("Dazzle").toLowerCase());
	commandFactory.registerCommand<DeactivateQuestCommand>(String("DeactivateQuest").toLowerCase());
	commandFactory.registerCommand<DeadBangCommand>(String("DeadBang").toLowerCase());
	commandFactory.registerCommand<DeathBlowCommand>(String("DeathBlow").toLowerCase());
	commandFactory.registerCommand<DeathCountCommand>(String("DeathCount").toLowerCase());
	commandFactory.registerCommand<DeclareOvertCommand>(String("DeclareOvert").toLowerCase());
	commandFactory.registerCommand<DeclareresidenceCommand>(String("Declareresidence").toLowerCase());
	commandFactory.registerCommand<DeclineCommand>(String("Decline").toLowerCase());
	commandFactory.registerCommand<DecontaminateCommand>(String("Decontaminate").toLowerCase());
	commandFactory.registerCommand<DecrepitStrikeCommand>(String("DecrepitStrike").toLowerCase());
	commandFactory.registerCommand<DefaultActionCommand>(String("DefaultAction").toLowerCase());
	commandFactory.registerCommand<DefaultAttackCommand>(String("DefaultAttack").toLowerCase());
	commandFactory.registerCommand<DefaultDroidAttackCommand>(String("DefaultDroidAttack").toLowerCase());
	commandFactory.registerCommand<DefuseMinefieldCommand>(String("DefuseMinefield").toLowerCase());
	commandFactory.registerCommand<DelegateFactionPointsCommand>(String("DelegateFactionPoints").toLowerCase());
	commandFactory.registerCommand<DemolitionShotCommand>(String("DemolitionShot").toLowerCase());
	commandFactory.registerCommand<DenyServiceCommand>(String("DenyService").toLowerCase());
	commandFactory.registerCommand<DeployTrapCommand>(String("DeployTrap").toLowerCase());
	commandFactory.registerCommand<DestroyCommand>(String("Destroy").toLowerCase());
	commandFactory.registerCommand<DestroyTargetCommand>(String("DestroyTarget").toLowerCase());
	commandFactory.registerCommand<DestroystructureCommand>(String("Destroystructure").toLowerCase());
	commandFactory.registerCommand<DetonateDroidCommand>(String("DetonateDroid").toLowerCase());
	commandFactory.registerCommand<DeuteriumTossCommand>(String("DeuteriumToss").toLowerCase());
	commandFactory.registerCommand<DiagnoseCommand>(String("Diagnose").toLowerCase());
	commandFactory.registerCommand<DisableTargetCommand>(String("DisableTarget").toLowerCase());
	commandFactory.registerCommand<DisarmingShotCommand>(String("DisarmingShot").toLowerCase());
	commandFactory.registerCommand<DisbandCommand>(String("Disband").toLowerCase());
	commandFactory.registerCommand<DiseaseInnoculationCommand>(String("DiseaseInnoculation").toLowerCase());
	commandFactory.registerCommand<DisinfectCommand>(String("Disinfect").toLowerCase());
	commandFactory.registerCommand<DismissGroupMemberCommand>(String("DismissGroupMember").toLowerCase());
	commandFactory.registerCommand<DismountCommand>(String("Dismount").toLowerCase());
	commandFactory.registerCommand<DismountandstoreCommand>(String("Dismountandstore").toLowerCase());
	commandFactory.registerCommand<DistractCommand>(String("Distract").toLowerCase());
	commandFactory.registerCommand<DiveShotCommand>(String("DiveShot").toLowerCase());
	commandFactory.registerCommand<DizzyAttackCommand>(String("DizzyAttack").toLowerCase());
	commandFactory.registerCommand<DizzyRecoveryCommand>(String("DizzyRecovery").toLowerCase());
	commandFactory.registerCommand<DockCommand>(String("Dock").toLowerCase());
	commandFactory.registerCommand<DominateMindCommand>(String("DominateMind").toLowerCase());
	commandFactory.registerCommand<DotPackCommand>(String("DotPack").toLowerCase());
	commandFactory.registerCommand<DoubleTimeCommand>(String("DoubleTime").toLowerCase());
	commandFactory.registerCommand<DragIncapacitatedPlayerCommand>(String("DragIncapacitatedPlayer").toLowerCase());
	commandFactory.registerCommand<DragPlayerCommand>(String("DragPlayer").toLowerCase());
	commandFactory.registerCommand<DrainForceCommand>(String("DrainForce").toLowerCase());
	commandFactory.registerCommand<DroidCommand>(String("Droid").toLowerCase());
	commandFactory.registerCommand<DuelCommand>(String("Duel").toLowerCase());
	commandFactory.registerCommand<DuelistStanceCommand>(String("DuelistStance").toLowerCase());
	commandFactory.registerCommand<DumpObjectInformationCommand>(String("DumpObjectInformation").toLowerCase());
	commandFactory.registerCommand<DumpTargetInformationCommand>(String("DumpTargetInformation").toLowerCase());
	commandFactory.registerCommand<DumpZoneInformationCommand>(String("DumpZoneInformation").toLowerCase());
	commandFactory.registerCommand<EatCommand>(String("Eat").toLowerCase());
	commandFactory.registerCommand<EditAppearanceCommand>(String("EditAppearance").toLowerCase());
	commandFactory.registerCommand<EditBankAccountCommand>(String("EditBankAccount").toLowerCase());
	commandFactory.registerCommand<EditBankCommand>(String("EditBank").toLowerCase());
	commandFactory.registerCommand<EditStatsCommand>(String("EditStats").toLowerCase());
	commandFactory.registerCommand<EjectCommand>(String("Eject").toLowerCase());
	commandFactory.registerCommand<ElectroliteDrainCommand>(String("ElectroliteDrain").toLowerCase());
	commandFactory.registerCommand<EmboldenpetsCommand>(String("Emboldenpets").toLowerCase());
	commandFactory.registerCommand<EmptyMailTargetCommand>(String("EmptyMailTarget").toLowerCase());
	commandFactory.registerCommand<EndDuelCommand>(String("EndDuel").toLowerCase());
	commandFactory.registerCommand<EndorphineInjectionCommand>(String("EndorphineInjection").toLowerCase());
	commandFactory.registerCommand<EnragepetsCommand>(String("Enragepets").toLowerCase());
	commandFactory.registerCommand<Epulse1Command>(String("Epulse1").toLowerCase());
	commandFactory.registerCommand<Epulse2Command>(String("Epulse2").toLowerCase());
	commandFactory.registerCommand<Epulse3Command>(String("Epulse3").toLowerCase());
	commandFactory.registerCommand<EquilibriumCommand>(String("Equilibrium").toLowerCase());
	commandFactory.registerCommand<EscapePodCommand>(String("EscapePod").toLowerCase());
	commandFactory.registerCommand<EshieldsCommand>(String("Eshields").toLowerCase());
	commandFactory.registerCommand<EthrustCommand>(String("Ethrust").toLowerCase());
	commandFactory.registerCommand<EuphoriaCommand>(String("Euphoria").toLowerCase());
	commandFactory.registerCommand<EventBuffAreaCommand>(String("EventBuffArea").toLowerCase());
	commandFactory.registerCommand<EventBuffCommand>(String("EventBuff").toLowerCase());
	commandFactory.registerCommand<EventBuffTargetCommand>(String("EventBuffTarget").toLowerCase());
	commandFactory.registerCommand<EventClearStatesCommand>(String("EventClearStates").toLowerCase());
	commandFactory.registerCommand<EventDamageCommand>(String("EventDamage").toLowerCase());
	commandFactory.registerCommand<EventMoveToMeCommand>(String("EventMoveToMe").toLowerCase());
	commandFactory.registerCommand<EventStorePetCommand>(String("EventStorePet").toLowerCase());
	commandFactory.registerCommand<EventTefAreaCommand>(String("EventTefArea").toLowerCase());
	commandFactory.registerCommand<EventTefClearCommand>(String("EventTefClear").toLowerCase());
	commandFactory.registerCommand<EventTefTargetCommand>(String("EventTefTarget").toLowerCase());
	commandFactory.registerCommand<EventUndoMoveToMeCommand>(String("EventUndoMoveToMe").toLowerCase());
	commandFactory.registerCommand<EventVaderChokeCommand>(String("EventVaderChoke").toLowerCase());
	commandFactory.registerCommand<EventWeaponCommand>(String("EventWeapon").toLowerCase());
	commandFactory.registerCommand<EweaponsCommand>(String("Eweapons").toLowerCase());
	commandFactory.registerCommand<ExecuteKnowledgeBaseMessageCommand>(String("ExecuteKnowledgeBaseMessage").toLowerCase());
	commandFactory.registerCommand<ExtinguishFireCommand>(String("ExtinguishFire").toLowerCase());
	commandFactory.registerCommand<ExtractObjectCommand>(String("ExtractObject").toLowerCase());
	commandFactory.registerCommand<EyeShotCommand>(String("EyeShot").toLowerCase());
	commandFactory.registerCommand<FactoryCrateSplitCommand>(String("FactoryCrateSplit").toLowerCase());
	commandFactory.registerCommand<FanShotCommand>(String("FanShot").toLowerCase());
	commandFactory.registerCommand<FeaturedSoloCommand>(String("FeaturedSolo").toLowerCase());
	commandFactory.registerCommand<FeignDeathCommand>(String("FeignDeath").toLowerCase());
	commandFactory.registerCommand<FindCommand>(String("Find").toLowerCase());
	commandFactory.registerCommand<FindFriendCommand>(String("FindFriend").toLowerCase());
	commandFactory.registerCommand<FindMyTrainerCommand>(String("FindMyTrainer").toLowerCase());
	commandFactory.registerCommand<FindObjectCommand>(String("FindObject").toLowerCase());
	commandFactory.registerCommand<FindPlayerCommand>(String("FindPlayer").toLowerCase());
	commandFactory.registerCommand<FirearmStrikeCommand>(String("FirearmStrike").toLowerCase());
	commandFactory.registerCommand<Firejet2Command>(String("Firejet2").toLowerCase());
	commandFactory.registerCommand<FirejetCommand>(String("Firejet").toLowerCase());
	commandFactory.registerCommand<FishCommand>(String("Fish").toLowerCase());
	commandFactory.registerCommand<FlashSpeederCommand>(String("FlashSpeeder").toLowerCase());
	commandFactory.registerCommand<FloCommand>(String("Flo").toLowerCase());
	commandFactory.registerCommand<FloorLightsCommand>(String("FloorLights").toLowerCase());
	commandFactory.registerCommand<FlourishCommand>(String("Flourish").toLowerCase());
	commandFactory.registerCommand<FocusFireCommand>(String("FocusFire").toLowerCase());
	commandFactory.registerCommand<ForageCommand>(String("Forage").toLowerCase());
	commandFactory.registerCommand<ForceAbsorbCommand>(String("ForceAbsorb").toLowerCase());
	commandFactory.registerCommand<ForceArmorCommand>(String("ForceArmor").toLowerCase());
	commandFactory.registerCommand<ForceAuraCommand>(String("ForceAura").toLowerCase());
	commandFactory.registerCommand<ForceBreachCommand>(String("ForceBreach").toLowerCase());
	commandFactory.registerCommand<ForceChokeCommand>(String("ForceChoke").toLowerCase());
	commandFactory.registerCommand<ForceCloakCommand>(String("ForceCloak").toLowerCase());
	commandFactory.registerCommand<ForceCommandCommand>(String("ForceCommand").toLowerCase());
	commandFactory.registerCommand<ForceCureDiseaseCommand>(String("ForceCureDisease").toLowerCase());
	commandFactory.registerCommand<ForceCurePoisonCommand>(String("ForceCurePoison").toLowerCase());
	commandFactory.registerCommand<ForceExtinguishCommand>(String("ForceExtinguish").toLowerCase());
	commandFactory.registerCommand<ForceFeedbackCommand>(String("ForceFeedback").toLowerCase());
	commandFactory.registerCommand<ForceHealCommand>(String("ForceHeal").toLowerCase());
	commandFactory.registerCommand<ForceHitCommand>(String("ForceHit").toLowerCase());
	commandFactory.registerCommand<ForceInfusionCommand>(String("ForceInfusion").toLowerCase());
	commandFactory.registerCommand<ForceIntimidateCommand>(String("ForceIntimidate").toLowerCase());
	commandFactory.registerCommand<ForceKnockdownCommand>(String("ForceKnockdown").toLowerCase());
	commandFactory.registerCommand<ForceLightningAreaCommand>(String("ForceLightningArea").toLowerCase());
	commandFactory.registerCommand<ForceLightningCommand>(String("ForceLightning").toLowerCase());
	commandFactory.registerCommand<ForceMeditateCommand>(String("ForceMeditate").toLowerCase());
	commandFactory.registerCommand<ForceOfWillCommand>(String("ForceOfWill").toLowerCase());
	commandFactory.registerCommand<ForceProtectionCommand>(String("ForceProtection").toLowerCase());
	commandFactory.registerCommand<ForceResistBleedingCommand>(String("ForceResistBleeding").toLowerCase());
	commandFactory.registerCommand<ForceResistDiseaseCommand>(String("ForceResistDisease").toLowerCase());
	commandFactory.registerCommand<ForceResistPoisonCommand>(String("ForceResistPoison").toLowerCase());
	commandFactory.registerCommand<ForceResistStatesCommand>(String("ForceResistStates").toLowerCase());
	commandFactory.registerCommand<ForceRunCommand>(String("ForceRun").toLowerCase());
	commandFactory.registerCommand<ForceRunCommand>(String("ForceRun_1").toLowerCase());
	commandFactory.registerCommand<ForceRunCommand>(String("ForceRun_2").toLowerCase());
	commandFactory.registerCommand<ForceSapCommand>(String("ForceSap").toLowerCase());
	commandFactory.registerCommand<ForceShieldCommand>(String("ForceShield").toLowerCase());
	commandFactory.registerCommand<ForceShockCommand>(String("ForceShock").toLowerCase());
	commandFactory.registerCommand<ForceSpeedCommand>(String("ForceSpeed").toLowerCase());
	commandFactory.registerCommand<ForceStrikeCommand>(String("ForceStrike").toLowerCase());
	commandFactory.registerCommand<ForceSuppressionCommand>(String("ForceSuppression").toLowerCase());
	commandFactory.registerCommand<ForceThrowCommand>(String("ForceThrow").toLowerCase());
	commandFactory.registerCommand<ForceValorCommand>(String("ForceValor").toLowerCase());
	commandFactory.registerCommand<ForceWaveCommand>(String("ForceWave").toLowerCase());
	commandFactory.registerCommand<ForceWeakenCommand>(String("ForceWeaken").toLowerCase());
	commandFactory.registerCommand<ForceWoundHealCommand>(String("ForceWoundHeal").toLowerCase());
	commandFactory.registerCommand<FormupCommand>(String("Formup").toLowerCase());
	commandFactory.registerCommand<FreezePlayerCommand>(String("FreezePlayer").toLowerCase());
	commandFactory.registerCommand<FullAutoAreaCommand>(String("FullAutoArea").toLowerCase());
	commandFactory.registerCommand<GCommand>(String("G").toLowerCase());
	commandFactory.registerCommand<GallopCommand>(String("Gallop").toLowerCase());
	commandFactory.registerCommand<GallopStopCommand>(String("GallopStop").toLowerCase());
	commandFactory.registerCommand<GcCommand>(String("Gc").toLowerCase());
	commandFactory.registerCommand<GcwStatusCommand>(String("GcwStatus").toLowerCase());
	commandFactory.registerCommand<GenerateCraftedItemCommand>(String("GenerateCraftedItem").toLowerCase());
	commandFactory.registerCommand<GetAccountInfoCommand>(String("GetAccountInfo").toLowerCase());
	commandFactory.registerCommand<GetAttributesBatchCommand>(String("GetAttributesBatch").toLowerCase());
	commandFactory.registerCommand<GetAttributesCommand>(String("GetAttributes").toLowerCase());
	commandFactory.registerCommand<GetFriendListCommand>(String("GetFriendList").toLowerCase());
	commandFactory.registerCommand<GetGameTimeCommand>(String("GetGameTime").toLowerCase());
	commandFactory.registerCommand<GetIgnoreListCommand>(String("GetIgnoreList").toLowerCase());
	commandFactory.registerCommand<GetMapLocationsCommand>(String("GetMapLocations").toLowerCase());
	commandFactory.registerCommand<GetObjVarsCommand>(String("GetObjVars").toLowerCase());
	commandFactory.registerCommand<GetPlayerIdCommand>(String("GetPlayerId").toLowerCase());
	commandFactory.registerCommand<GetPrototypeCommand>(String("GetPrototype").toLowerCase());
	commandFactory.registerCommand<GetRankCommand>(String("GetRank").toLowerCase());
	commandFactory.registerCommand<GetSpawnDelaysCommand>(String("GetSpawnDelays").toLowerCase());
	commandFactory.registerCommand<GetStationNameCommand>(String("GetStationName").toLowerCase());
	commandFactory.registerCommand<GetVeteranRewardTimeCommand>(String("GetVeteranRewardTime").toLowerCase());
	commandFactory.registerCommand<GetVeteranRewardTimeCsCommand>(String("GetVeteranRewardTimeCs").toLowerCase());
	commandFactory.registerCommand<GiveItemCommand>(String("GiveItem").toLowerCase());
	commandFactory.registerCommand<GiveMaintenanceToVendorCommand>(String("GiveMaintenanceToVendor").toLowerCase());
	commandFactory.registerCommand<GivevendormaintCommand>(String("Givevendormaint").toLowerCase());
	commandFactory.registerCommand<GmCreateClassResourceCommand>(String("GmCreateClassResource").toLowerCase());
	commandFactory.registerCommand<GmCreateSpecificResourceCommand>(String("GmCreateSpecificResource").toLowerCase());
	commandFactory.registerCommand<GmForceCommandCommand>(String("GmForceCommand").toLowerCase());
	commandFactory.registerCommand<GmForceRankCommand>(String("GmForceRank").toLowerCase());
	commandFactory.registerCommand<GmFsVillageCommand>(String("GmFsVillage").toLowerCase());
	commandFactory.registerCommand<GmJediStateCommand>(String("GmJediState").toLowerCase());
	commandFactory.registerCommand<GmReviveCommand>(String("GmRevive").toLowerCase());
	commandFactory.registerCommand<GmWeaponCommand>(String("GmWeapon").toLowerCase());
	commandFactory.registerCommand<GotoCommand>(String("Goto").toLowerCase());
	commandFactory.registerCommand<GrantBadgeAreaCommand>(String("GrantBadgeArea").toLowerCase());
	commandFactory.registerCommand<GrantBadgeCommand>(String("GrantBadge").toLowerCase());
	commandFactory.registerCommand<GrantPadawanTrialsEligibilityCommand>(String("GrantPadawanTrialsEligibility").toLowerCase());
	commandFactory.registerCommand<GrantSkillCommand>(String("GrantSkill").toLowerCase());
	commandFactory.registerCommand<GrantTitleCommand>(String("GrantTitle").toLowerCase());
	commandFactory.registerCommand<GrantZoningRightsCommand>(String("GrantZoningRights").toLowerCase());
	commandFactory.registerCommand<GroupChatCommand>(String("GroupChat").toLowerCase());
	commandFactory.registerCommand<GroupLootCommand>(String("GroupLoot").toLowerCase());
	commandFactory.registerCommand<GuildCommand>(String("Guild").toLowerCase());
	commandFactory.registerCommand<GuildremoveCommand>(String("Guildremove").toLowerCase());
	commandFactory.registerCommand<GuildstatusCommand>(String("Guildstatus").toLowerCase());
	commandFactory.registerCommand<HandleClientLoginCommand>(String("HandleClientLogin").toLowerCase());
	commandFactory.registerCommand<HarmfulCommand>(String("Harmful").toLowerCase());
	commandFactory.registerCommand<HarmlessCommand>(String("Harmless").toLowerCase());
	commandFactory.registerCommand<HarvestCorpseCommand>(String("HarvestCorpse").toLowerCase());
	commandFactory.registerCommand<HarvesterActivateCommand>(String("HarvesterActivate").toLowerCase());
	commandFactory.registerCommand<HarvesterDeactivateCommand>(String("HarvesterDeactivate").toLowerCase());
	commandFactory.registerCommand<HarvesterDiscardHopperCommand>(String("HarvesterDiscardHopper").toLowerCase());
	commandFactory.registerCommand<HarvesterGetResourceDataCommand>(String("HarvesterGetResourceData").toLowerCase());
	commandFactory.registerCommand<HarvesterHarvestCommand>(String("HarvesterHarvest").toLowerCase());
	commandFactory.registerCommand<HarvesterMakeCrateCommand>(String("HarvesterMakeCrate").toLowerCase());
	commandFactory.registerCommand<HarvesterSelectResourceCommand>(String("HarvesterSelectResource").toLowerCase());
	commandFactory.registerCommand<HarvesterTakeSurveyCommand>(String("HarvesterTakeSurvey").toLowerCase());
	commandFactory.registerCommand<HasVeteranRewardCommand>(String("HasVeteranReward").toLowerCase());
	commandFactory.registerCommand<HaveconsentCommand>(String("Haveconsent").toLowerCase());
	commandFactory.registerCommand<HeadHitCommand>(String("HeadHit").toLowerCase());
	commandFactory.registerCommand<HeadShotCommand>(String("HeadShot").toLowerCase());
	commandFactory.registerCommand<HealDroidDamageCommand>(String("HealDroidDamage").toLowerCase());
	commandFactory.registerCommand<HealDroidWoundCommand>(String("HealDroidWound").toLowerCase());
	commandFactory.registerCommand<HealPetCommand>(String("HealPet").toLowerCase());
	commandFactory.registerCommand<HealStateCommand>(String("HealState").toLowerCase());
	commandFactory.registerCommand<HealStatesCommand>(String("HealStates").toLowerCase());
	commandFactory.registerCommand<HealWoundCommand>(String("HealWound").toLowerCase());
	commandFactory.registerCommand<HemmorrhageCommand>(String("Hemmorrhage").toLowerCase());
	commandFactory.registerCommand<HighYieldCommand>(String("HighYield").toLowerCase());
	commandFactory.registerCommand<HoloEmoteCommand>(String("HoloEmote").toLowerCase());
	commandFactory.registerCommand<HyperspaceCommand>(String("Hyperspace").toLowerCase());
	commandFactory.registerCommand<IffscrambleCommand>(String("Iffscramble").toLowerCase());
	commandFactory.registerCommand<ImagedesignCommand>(String("Imagedesign").toLowerCase());
	commandFactory.registerCommand<ImpaleCommand>(String("Impale").toLowerCase());
	commandFactory.registerCommand<InfectCommand>(String("Infect").toLowerCase());
	commandFactory.registerCommand<InitializeComponentCommand>(String("InitializeComponent").toLowerCase());
	commandFactory.registerCommand<InnateCommand>(String("Innate").toLowerCase());
	commandFactory.registerCommand<InsertItemIntoShipComponentSlotCommand>(String("InsertItemIntoShipComponentSlot").toLowerCase());
	commandFactory.registerCommand<InsidiousMaladyCommand>(String("InsidiousMalady").toLowerCase());
	commandFactory.registerCommand<InspacereloadCommand>(String("Inspacereload").toLowerCase());
	commandFactory.registerCommand<InspacerepairCommand>(String("Inspacerepair").toLowerCase());
	commandFactory.registerCommand<InspacerrCommand>(String("Inspacerr").toLowerCase());
	commandFactory.registerCommand<InspectCommand>(String("Inspect").toLowerCase());
	commandFactory.registerCommand<InspireCommand>(String("Inspire").toLowerCase());
	commandFactory.registerCommand<InstallMissionTerminalCommand>(String("InstallMissionTerminal").toLowerCase());
	commandFactory.registerCommand<InstallShipComponentCommand>(String("InstallShipComponent").toLowerCase());
	commandFactory.registerCommand<InsureCommand>(String("Insure").toLowerCase());
	commandFactory.registerCommand<IntimidateCommand>(String("Intimidate").toLowerCase());
	commandFactory.registerCommand<IntimidateShotCommand>(String("IntimidateShot").toLowerCase());
	commandFactory.registerCommand<IntimidationAttackCommand>(String("IntimidationAttack").toLowerCase());
	commandFactory.registerCommand<InviteCommand>(String("Invite").toLowerCase());
	commandFactory.registerCommand<InvulnerableCommand>(String("Invulnerable").toLowerCase());
	commandFactory.registerCommand<ItemmovebackCommand>(String("Itemmoveback").toLowerCase());
	commandFactory.registerCommand<ItemmovedownCommand>(String("Itemmovedown").toLowerCase());
	commandFactory.registerCommand<ItemmoveforwardCommand>(String("Itemmoveforward").toLowerCase());
	commandFactory.registerCommand<ItemmoveupCommand>(String("Itemmoveup").toLowerCase());
	commandFactory.registerCommand<ItemrotateleftCommand>(String("Itemrotateleft").toLowerCase());
	commandFactory.registerCommand<ItemrotaterightCommand>(String("Itemrotateright").toLowerCase());
	commandFactory.registerCommand<JediMindTrickCommand>(String("JediMindTrick").toLowerCase());
	commandFactory.registerCommand<JoinCommand>(String("Join").toLowerCase());
	commandFactory.registerCommand<JoinGameCommand>(String("JoinGame").toLowerCase());
	commandFactory.registerCommand<Jstart1Command>(String("Jstart1").toLowerCase());
	commandFactory.registerCommand<Jstart2Command>(String("Jstart2").toLowerCase());
	commandFactory.registerCommand<Jstart3Command>(String("Jstart3").toLowerCase());
	commandFactory.registerCommand<KickCommand>(String("Kick").toLowerCase());
	commandFactory.registerCommand<KillCommand>(String("Kill").toLowerCase());
	commandFactory.registerCommand<KillPlayerCommand>(String("KillPlayer").toLowerCase());
	commandFactory.registerCommand<KipUpShotCommand>(String("KipUpShot").toLowerCase());
	commandFactory.registerCommand<KneecapShotCommand>(String("KneecapShot").toLowerCase());
	commandFactory.registerCommand<KneelCommand>(String("Kneel").toLowerCase());
	commandFactory.registerCommand<KnockdownAttackCommand>(String("KnockdownAttack").toLowerCase());
	commandFactory.registerCommand<KnockdownFireCommand>(String("KnockdownFire").toLowerCase());
	commandFactory.registerCommand<KnockdownRecoveryCommand>(String("KnockdownRecovery").toLowerCase());
	commandFactory.registerCommand<LagCommand>(String("Lag").toLowerCase());
	commandFactory.registerCommand<LaserShowCommand>(String("LaserShow").toLowerCase());
	commandFactory.registerCommand<LastDitchCommand>(String("LastDitch").toLowerCase());
	commandFactory.registerCommand<LaunchCountermeasureCommand>(String("LaunchCountermeasure").toLowerCase());
	commandFactory.registerCommand<LaunchFireworkCommand>(String("LaunchFirework").toLowerCase());
	commandFactory.registerCommand<LaunchIntoSpaceCommand>(String("LaunchIntoSpace").toLowerCase());
	commandFactory.registerCommand<LaunchMissileCommand>(String("LaunchMissile").toLowerCase());
	commandFactory.registerCommand<LeaveGameCommand>(String("LeaveGame").toLowerCase());
	commandFactory.registerCommand<LeaveGroupCommand>(String("LeaveGroup").toLowerCase());
	commandFactory.registerCommand<LeaveStationCommand>(String("LeaveStation").toLowerCase());
	commandFactory.registerCommand<LegHitCommand>(String("LegHit").toLowerCase());
	commandFactory.registerCommand<LegShotCommand>(String("LegShot").toLowerCase());
	commandFactory.registerCommand<LegSweepCommand>(String("LegSweep").toLowerCase());
	commandFactory.registerCommand<LethalShotCommand>(String("LethalShot").toLowerCase());
	commandFactory.registerCommand<LfgCommand>(String("Lfg").toLowerCase());
	commandFactory.registerCommand<LightEngineScrambleCommand>(String("LightEngineScramble").toLowerCase());
	commandFactory.registerCommand<ListActiveQuestsCommand>(String("ListActiveQuests").toLowerCase());
	commandFactory.registerCommand<ListCompletedQuestsCommand>(String("ListCompletedQuests").toLowerCase());
	commandFactory.registerCommand<ListGuildsCommand>(String("ListGuilds").toLowerCase());
	commandFactory.registerCommand<ListenCommand>(String("Listen").toLowerCase());
	commandFactory.registerCommand<LogoutCommand>(String("Logout").toLowerCase());
	commandFactory.registerCommand<LogoutServerCommand>(String("LogoutServer").toLowerCase());
	commandFactory.registerCommand<LootAiCorpseCommand>(String("LootAiCorpse").toLowerCase());
	commandFactory.registerCommand<LootAllCommand>(String("LootAll").toLowerCase());
	commandFactory.registerCommand<LootCommand>(String("Loot").toLowerCase());
	commandFactory.registerCommand<LootPlayerCorpseCommand>(String("LootPlayerCorpse").toLowerCase());
	commandFactory.registerCommand<LowBlowCommand>(String("LowBlow").toLowerCase());
	commandFactory.registerCommand<LungeCommand>(String("Lunge").toLowerCase());
	commandFactory.registerCommand<MakeLeaderCommand>(String("MakeLeader").toLowerCase());
	commandFactory.registerCommand<MakeMasterLooterCommand>(String("MakeMasterLooter").toLowerCase());
	commandFactory.registerCommand<MakeSurveyCommand>(String("MakeSurvey").toLowerCase());
	commandFactory.registerCommand<ManufactureCommand>(String("Manufacture").toLowerCase());
	commandFactory.registerCommand<MaskscentCommand>(String("Maskscent").toLowerCase());
	commandFactory.registerCommand<MaxCombatAbilityCommand>(String("MaxCombatAbility").toLowerCase());
	commandFactory.registerCommand<MaxForcePowerCommand>(String("MaxForcePower").toLowerCase());
	commandFactory.registerCommand<MaxStatsCommand>(String("MaxStats").toLowerCase());
	commandFactory.registerCommand<MedicalForageCommand>(String("MedicalForage").toLowerCase());
	commandFactory.registerCommand<MeditateCommand>(String("Meditate").toLowerCase());
	commandFactory.registerCommand<MeleeAssaultCommand>(String("MeleeAssault").toLowerCase());
	commandFactory.registerCommand<MeleeHitCommand>(String("MeleeHit").toLowerCase());
	commandFactory.registerCommand<MeleeStrikeCommand>(String("MeleeStrike").toLowerCase());
	commandFactory.registerCommand<MindBlastCommand>(String("MindBlast").toLowerCase());
	commandFactory.registerCommand<MinefieldAttackCommand>(String("MinefieldAttack").toLowerCase());
	commandFactory.registerCommand<MoneyCommand>(String("Money").toLowerCase());
	commandFactory.registerCommand<MountCommand>(String("Mount").toLowerCase());
	commandFactory.registerCommand<MoveFurnitureCommand>(String("MoveFurniture").toLowerCase());
	commandFactory.registerCommand<MultiTargetPistolShotCommand>(String("MultiTargetPistolShot").toLowerCase());
	commandFactory.registerCommand<MultiTargetShotCommand>(String("MultiTargetShot").toLowerCase());
	commandFactory.registerCommand<NameStructureCommand>(String("NameStructure").toLowerCase());
	commandFactory.registerCommand<NblastCommand>(String("Nblast").toLowerCase());
	commandFactory.registerCommand<NeurotoxinCommand>(String("Neurotoxin").toLowerCase());
	commandFactory.registerCommand<NewbieRequestStartingLocationsCommand>(String("NewbieRequestStartingLocations").toLowerCase());
	commandFactory.registerCommand<NewbieSelectStartingLocationCommand>(String("NewbieSelectStartingLocation").toLowerCase());
	commandFactory.registerCommand<NewbiehelperCommand>(String("Newbiehelper").toLowerCase());
	commandFactory.registerCommand<NextCraftingStageCommand>(String("NextCraftingStage").toLowerCase());
	commandFactory.registerCommand<NpcCommand>(String("Npc").toLowerCase());
	commandFactory.registerCommand<NpcConversationSelectCommand>(String("NpcConversationSelect").toLowerCase());
	commandFactory.registerCommand<NpcConversationStartCommand>(String("NpcConversationStart").toLowerCase());
	commandFactory.registerCommand<NpcConversationStopCommand>(String("NpcConversationStop").toLowerCase());
	commandFactory.registerCommand<NutrientInjectionCommand>(String("NutrientInjection").toLowerCase());
	commandFactory.registerCommand<ObjectCommand>(String("Object").toLowerCase());
	commandFactory.registerCommand<ObjvarCommand>(String("Objvar").toLowerCase());
	commandFactory.registerCommand<OpenContainerCommand>(String("OpenContainer").toLowerCase());
	commandFactory.registerCommand<OpenLotteryContainerCommand>(String("OpenLotteryContainer").toLowerCase());
	commandFactory.registerCommand<OpenWingsCommand>(String("OpenWings").toLowerCase());
	commandFactory.registerCommand<OverchargeShotCommand>(String("OverchargeShot").toLowerCase());
	commandFactory.registerCommand<OverkillShotCommand>(String("OverkillShot").toLowerCase());
	commandFactory.registerCommand<OverrideActiveMonthsCommand>(String("OverrideActiveMonths").toLowerCase());
	commandFactory.registerCommand<OverridePadawanTrialsEligibilityCommand>(String("OverridePadawanTrialsEligibility").toLowerCase());
	commandFactory.registerCommand<OverwhelmingShotCommand>(String("OverwhelmingShot").toLowerCase());
	commandFactory.registerCommand<PaWithdrawCommand>(String("PaWithdraw").toLowerCase());
	commandFactory.registerCommand<PaintTargetCommand>(String("PaintTarget").toLowerCase());
	commandFactory.registerCommand<PanicShotCommand>(String("PanicShot").toLowerCase());
	commandFactory.registerCommand<ParalyzeCommand>(String("Paralyze").toLowerCase());
	commandFactory.registerCommand<ParryRiposteCommand>(String("ParryRiposte").toLowerCase());
	commandFactory.registerCommand<PauseDanceCommand>(String("PauseDance").toLowerCase());
	commandFactory.registerCommand<PauseMusicCommand>(String("PauseMusic").toLowerCase());
	commandFactory.registerCommand<PaymaintenanceCommand>(String("Paymaintenance").toLowerCase());
	commandFactory.registerCommand<PeaceCommand>(String("Peace").toLowerCase());
	commandFactory.registerCommand<PermissionListModifyCommand>(String("PermissionListModify").toLowerCase());
	commandFactory.registerCommand<PetBleedAttackCommand>(String("PetBleedAttack").toLowerCase());
	commandFactory.registerCommand<PetBlindAttackCommand>(String("PetBlindAttack").toLowerCase());
	commandFactory.registerCommand<PetDefenseBreakAttackCommand>(String("PetDefenseBreakAttack").toLowerCase());
	commandFactory.registerCommand<PetIntimidateAttackCommand>(String("PetIntimidateAttack").toLowerCase());
	commandFactory.registerCommand<PetKnockdownAttackCommand>(String("PetKnockdownAttack").toLowerCase());
	commandFactory.registerCommand<PetPinAttackCommand>(String("PetPinAttack").toLowerCase());
	commandFactory.registerCommand<PetStunAttackCommand>(String("PetStunAttack").toLowerCase());
	commandFactory.registerCommand<PilotShipCommand>(String("PilotShip").toLowerCase());
	commandFactory.registerCommand<PistolWhipCommand>(String("PistolWhip").toLowerCase());
	commandFactory.registerCommand<PlaceBattlefieldStructureCommand>(String("PlaceBattlefieldStructure").toLowerCase());
	commandFactory.registerCommand<PlaceStructureCommand>(String("PlaceStructure").toLowerCase());
	commandFactory.registerCommand<PlaceStructureModeCommand>(String("PlaceStructureMode").toLowerCase());
	commandFactory.registerCommand<PlacedShotCommand>(String("PlacedShot").toLowerCase());
	commandFactory.registerCommand<PlanetCommand>(String("Planet").toLowerCase());
	commandFactory.registerCommand<PlanetsayCommand>(String("Planetsay").toLowerCase());
	commandFactory.registerCommand<PlanetwarpCommand>(String("Planetwarp").toLowerCase());
	commandFactory.registerCommand<PlanetwarpTargetCommand>(String("PlanetwarpTarget").toLowerCase());
	commandFactory.registerCommand<PointBlankAreaCommand>(String("PointBlankArea").toLowerCase());
	commandFactory.registerCommand<PointBlankShotCommand>(String("PointBlankShot").toLowerCase());
	commandFactory.registerCommand<PoisonInnoculationCommand>(String("PoisonInnoculation").toLowerCase());
	commandFactory.registerCommand<PostureDownAttackCommand>(String("PostureDownAttack").toLowerCase());
	commandFactory.registerCommand<PostureUpAttackCommand>(String("PostureUpAttack").toLowerCase());
	commandFactory.registerCommand<PowerAttackCommand>(String("PowerAttack").toLowerCase());
	commandFactory.registerCommand<PowerBoostCommand>(String("PowerBoost").toLowerCase());
	commandFactory.registerCommand<ProneCommand>(String("Prone").toLowerCase());
	commandFactory.registerCommand<Ptrap1Command>(String("Ptrap1").toLowerCase());
	commandFactory.registerCommand<Ptrap2Command>(String("Ptrap2").toLowerCase());
	commandFactory.registerCommand<PumpreactorCommand>(String("Pumpreactor").toLowerCase());
	commandFactory.registerCommand<PurchaseReinforcementCommand>(String("PurchaseReinforcement").toLowerCase());
	commandFactory.registerCommand<PurchaseTicketCommand>(String("PurchaseTicket").toLowerCase());
	commandFactory.registerCommand<QatoolCommand>(String("Qatool").toLowerCase());
	commandFactory.registerCommand<QuickDrawCommand>(String("QuickDraw").toLowerCase());
	commandFactory.registerCommand<RallyCommand>(String("Rally").toLowerCase());
	commandFactory.registerCommand<RallyPointCommand>(String("RallyPoint").toLowerCase());
	commandFactory.registerCommand<RampageCommand>(String("Rampage").toLowerCase());
	commandFactory.registerCommand<RangedShotCommand>(String("RangedShot").toLowerCase());
	commandFactory.registerCommand<RapidFireCommand>(String("RapidFire").toLowerCase());
	commandFactory.registerCommand<RecklessShotCommand>(String("RecklessShot").toLowerCase());
	commandFactory.registerCommand<ReconnectToTransferServerCommand>(String("ReconnectToTransferServer").toLowerCase());
	commandFactory.registerCommand<RecruitSkillTrainerCommand>(String("RecruitSkillTrainer").toLowerCase());
	commandFactory.registerCommand<RegainConsciousnessCommand>(String("RegainConsciousness").toLowerCase());
	commandFactory.registerCommand<RegenerationCommand>(String("Regeneration").toLowerCase());
	commandFactory.registerCommand<RegisterWithLocationCommand>(String("RegisterWithLocation").toLowerCase());
	commandFactory.registerCommand<ReloadCommand>(String("Reload").toLowerCase());
	commandFactory.registerCommand<RemoteCommand>(String("Remote").toLowerCase());
	commandFactory.registerCommand<RemoveAllowedPlayerCommand>(String("RemoveAllowedPlayer").toLowerCase());
	commandFactory.registerCommand<RemoveBannedPlayerCommand>(String("RemoveBannedPlayer").toLowerCase());
	commandFactory.registerCommand<RemoveFriendCommand>(String("RemoveFriend").toLowerCase());
	commandFactory.registerCommand<RemoveIgnoreCommand>(String("RemoveIgnore").toLowerCase());
	commandFactory.registerCommand<RepairBattlefieldStructureCommand>(String("RepairBattlefieldStructure").toLowerCase());
	commandFactory.registerCommand<RepairShipComponentInSlotCommand>(String("RepairShipComponentInSlot").toLowerCase());
	commandFactory.registerCommand<ReportCommand>(String("Report").toLowerCase());
	commandFactory.registerCommand<RequestBadgesCommand>(String("RequestBadges").toLowerCase());
	commandFactory.registerCommand<RequestBiographyCommand>(String("RequestBiography").toLowerCase());
	commandFactory.registerCommand<RequestCharacterMatchCommand>(String("RequestCharacterMatch").toLowerCase());
	commandFactory.registerCommand<RequestCharacterSheetInfoCommand>(String("RequestCharacterSheetInfo").toLowerCase());
	commandFactory.registerCommand<RequestCoreSampleCommand>(String("RequestCoreSample").toLowerCase());
	commandFactory.registerCommand<RequestCraftingSessionCommand>(String("RequestCraftingSession").toLowerCase());
	commandFactory.registerCommand<RequestDraftSlotsBatchCommand>(String("RequestDraftSlotsBatch").toLowerCase());
	commandFactory.registerCommand<RequestDraftSlotsCommand>(String("RequestDraftSlots").toLowerCase());
	commandFactory.registerCommand<RequestManfSchematicSlotsCommand>(String("RequestManfSchematicSlots").toLowerCase());
	commandFactory.registerCommand<RequestQuestTimersAndCountersCommand>(String("RequestQuestTimersAndCounters").toLowerCase());
	commandFactory.registerCommand<RequestResourceWeightsBatchCommand>(String("RequestResourceWeightsBatch").toLowerCase());
	commandFactory.registerCommand<RequestResourceWeightsCommand>(String("RequestResourceWeights").toLowerCase());
	commandFactory.registerCommand<RequestSetStatMigrationDataCommand>(String("RequestSetStatMigrationData").toLowerCase());
	commandFactory.registerCommand<RequestSpaceTrainerCommand>(String("RequestSpaceTrainer").toLowerCase());
	commandFactory.registerCommand<RequestStatMigrationDataCommand>(String("RequestStatMigrationData").toLowerCase());
	commandFactory.registerCommand<RequestStatMigrationStartCommand>(String("RequestStatMigrationStart").toLowerCase());
	commandFactory.registerCommand<RequestStatMigrationStopCommand>(String("RequestStatMigrationStop").toLowerCase());
	commandFactory.registerCommand<RequestStimpackCommand>(String("RequestStimpack").toLowerCase());
	commandFactory.registerCommand<RequestSurveyCommand>(String("RequestSurvey").toLowerCase());
	commandFactory.registerCommand<RequestWaypointAtPositionCommand>(String("RequestWaypointAtPosition").toLowerCase());
	commandFactory.registerCommand<ResSampleLoopCommand>(String("ResSampleLoop").toLowerCase());
	commandFactory.registerCommand<RescueCommand>(String("Rescue").toLowerCase());
	commandFactory.registerCommand<ResendLoginMessageToAllCommand>(String("ResendLoginMessageToAll").toLowerCase());
	commandFactory.registerCommand<ResetJediCommand>(String("ResetJedi").toLowerCase());
	commandFactory.registerCommand<ResourceCommand>(String("Resource").toLowerCase());
	commandFactory.registerCommand<ResourceContainerSplitCommand>(String("ResourceContainerSplit").toLowerCase());
	commandFactory.registerCommand<ResourceContainerTransferCommand>(String("ResourceContainerTransfer").toLowerCase());
	commandFactory.registerCommand<ResourceSetNameCommand>(String("ResourceSetName").toLowerCase());
	commandFactory.registerCommand<RespecStatCommitCommand>(String("RespecStatCommit").toLowerCase());
	commandFactory.registerCommand<RestartConversionCommand>(String("RestartConversion").toLowerCase());
	commandFactory.registerCommand<RestartCraftingSessionCommand>(String("RestartCraftingSession").toLowerCase());
	commandFactory.registerCommand<RestrainingShotCommand>(String("RestrainingShot").toLowerCase());
	commandFactory.registerCommand<ResuscitatePlayerCommand>(String("ResuscitatePlayer").toLowerCase());
	commandFactory.registerCommand<RetreatCommand>(String("Retreat").toLowerCase());
	commandFactory.registerCommand<RevivePlayerCommand>(String("RevivePlayer").toLowerCase());
	commandFactory.registerCommand<RevokeBadgeCommand>(String("RevokeBadge").toLowerCase());
	commandFactory.registerCommand<RevokeSkillCommand>(String("RevokeSkill").toLowerCase());
	commandFactory.registerCommand<RolePlayCommand>(String("RolePlay").toLowerCase());
	commandFactory.registerCommand<RollShotCommand>(String("RollShot").toLowerCase());
	commandFactory.registerCommand<RotateFurnitureCommand>(String("RotateFurniture").toLowerCase());
	commandFactory.registerCommand<SaberArmorBreakCommand>(String("SaberArmorBreak").toLowerCase());
	commandFactory.registerCommand<SaberBlindCommand>(String("SaberBlind").toLowerCase());
	commandFactory.registerCommand<SaberBodyHitCommand>(String("SaberBodyHit").toLowerCase());
	commandFactory.registerCommand<SaberDervishCommand>(String("SaberDervish").toLowerCase());
	commandFactory.registerCommand<SaberHeadHitCommand>(String("SaberHeadHit").toLowerCase());
	commandFactory.registerCommand<SaberHitCommand>(String("SaberHit").toLowerCase());
	commandFactory.registerCommand<SaberLegHitCommand>(String("SaberLegHit").toLowerCase());
	commandFactory.registerCommand<SaberPowerAttackCommand>(String("SaberPowerAttack").toLowerCase());
	commandFactory.registerCommand<SaberSlashCommand>(String("SaberSlash").toLowerCase());
	commandFactory.registerCommand<SaberSpinAttackCommand>(String("SaberSpinAttack").toLowerCase());
	commandFactory.registerCommand<SaberStrikeCommand>(String("SaberStrike").toLowerCase());
	commandFactory.registerCommand<SaberStunStrikeCommand>(String("SaberStunStrike").toLowerCase());
	commandFactory.registerCommand<SaberSweepCommand>(String("SaberSweep").toLowerCase());
	commandFactory.registerCommand<SaberSwipeCommand>(String("SaberSwipe").toLowerCase());
	commandFactory.registerCommand<SaberThrowCommand>(String("SaberThrow").toLowerCase());
	commandFactory.registerCommand<SampleCommand>(String("Sample").toLowerCase());
	commandFactory.registerCommand<SampleDNACommand>(String("SampleDNA").toLowerCase());
	commandFactory.registerCommand<ScatterHitCommand>(String("ScatterHit").toLowerCase());
	commandFactory.registerCommand<ScatterShotCommand>(String("ScatterShot").toLowerCase());
	commandFactory.registerCommand<ScriptCommand>(String("Script").toLowerCase());
	commandFactory.registerCommand<SeGogglesCommand>(String("SeGoggles").toLowerCase());
	commandFactory.registerCommand<SearchCorpseCommand>(String("SearchCorpse").toLowerCase());
	commandFactory.registerCommand<SecondChanceCommand>(String("SecondChance").toLowerCase());
	commandFactory.registerCommand<SecretSpawnSpamCommand>(String("SecretSpawnSpam").toLowerCase());
	commandFactory.registerCommand<SeethingAngerCommand>(String("SeethingAnger").toLowerCase());
	commandFactory.registerCommand<SelectDraftSchematicCommand>(String("SelectDraftSchematic").toLowerCase());
	commandFactory.registerCommand<SendFormObjectDataCommand>(String("SendFormObjectData").toLowerCase());
	commandFactory.registerCommand<SerotoninInjectionCommand>(String("SerotoninInjection").toLowerCase());
	commandFactory.registerCommand<ServerAsteroidDataListenCommand>(String("ServerAsteroidDataListen").toLowerCase());
	commandFactory.registerCommand<ServerAsteroidDataStopListeningCommand>(String("ServerAsteroidDataStopListening").toLowerCase());
	commandFactory.registerCommand<ServerCommand>(String("Server").toLowerCase());
	commandFactory.registerCommand<ServerDestroyObjectCommand>(String("ServerDestroyObject").toLowerCase());
	commandFactory.registerCommand<ServerSysGroupCommand>(String("ServerSysGroup").toLowerCase());
	commandFactory.registerCommand<SetBiographyAdminCommand>(String("SetBiographyAdmin").toLowerCase());
	commandFactory.registerCommand<SetBiographyCommand>(String("SetBiography").toLowerCase());
	commandFactory.registerCommand<SetBlazeOfGloryCommand>(String("SetBlazeOfGlory").toLowerCase());
	commandFactory.registerCommand<SetBoostmoraleCommand>(String("SetBoostmorale").toLowerCase());
	commandFactory.registerCommand<SetCallToArmsCommand>(String("SetCallToArms").toLowerCase());
	commandFactory.registerCommand<SetCalledShotCommand>(String("SetCalledShot").toLowerCase());
	commandFactory.registerCommand<SetChargeCommand>(String("SetCharge").toLowerCase());
	commandFactory.registerCommand<SetCombatFeintCommand>(String("SetCombatFeint").toLowerCase());
	commandFactory.registerCommand<SetCurrentSkillTitleCommand>(String("SetCurrentSkillTitle").toLowerCase());
	commandFactory.registerCommand<SetDoubleTimeCommand>(String("SetDoubleTime").toLowerCase());
	commandFactory.registerCommand<SetExperienceCommand>(String("SetExperience").toLowerCase());
	commandFactory.registerCommand<SetFactionCommand>(String("SetFaction").toLowerCase());
	commandFactory.registerCommand<SetFactionStandingCommand>(String("SetFactionStanding").toLowerCase());
	commandFactory.registerCommand<SetFirstNameCommand>(String("SetFirstName").toLowerCase());
	commandFactory.registerCommand<SetFormupCommand>(String("SetFormup").toLowerCase());
	commandFactory.registerCommand<SetGodModeCommand>(String("SetGodMode").toLowerCase());
	commandFactory.registerCommand<SetGrievousAuthorizedCommand>(String("SetGrievousAuthorized").toLowerCase());
	commandFactory.registerCommand<SetGroupXPBonusCommand>(String("SetGroupXPBonus").toLowerCase());
	commandFactory.registerCommand<SetHighYieldCommand>(String("SetHighYield").toLowerCase());
	commandFactory.registerCommand<SetHueCommand>(String("SetHue").toLowerCase());
	commandFactory.registerCommand<SetIntimidateCommand>(String("SetIntimidate").toLowerCase());
	commandFactory.registerCommand<SetLastNameCommand>(String("SetLastName").toLowerCase());
	commandFactory.registerCommand<SetLoginMessageCommand>(String("SetLoginMessage").toLowerCase());
	commandFactory.registerCommand<SetLoginTitleCommand>(String("SetLoginTitle").toLowerCase());
	commandFactory.registerCommand<SetMatchMakingCharacterIdCommand>(String("SetMatchMakingCharacterId").toLowerCase());
	commandFactory.registerCommand<SetMatchMakingPersonalIdCommand>(String("SetMatchMakingPersonalId").toLowerCase());
	commandFactory.registerCommand<SetMaximumSpawnTimeCommand>(String("SetMaximumSpawnTime").toLowerCase());
	commandFactory.registerCommand<SetMinimumSpawnTimeCommand>(String("SetMinimumSpawnTime").toLowerCase());
	commandFactory.registerCommand<SetMoodCommand>(String("SetMood").toLowerCase());
	commandFactory.registerCommand<SetMoodInternalCommand>(String("SetMoodInternal").toLowerCase());
	commandFactory.registerCommand<SetNameCommand>(String("SetName").toLowerCase());
	commandFactory.registerCommand<SetOwnerCommand>(String("SetOwner").toLowerCase());
	commandFactory.registerCommand<SetPaintTargetCommand>(String("SetPaintTarget").toLowerCase());
	commandFactory.registerCommand<SetPerformanceBuffTargetCommand>(String("SetPerformanceBuffTarget").toLowerCase());
	commandFactory.registerCommand<SetPlanetLimitCommand>(String("SetPlanetLimit").toLowerCase());
	commandFactory.registerCommand<SetPlayerAppearanceCommand>(String("SetPlayerAppearance").toLowerCase());
	commandFactory.registerCommand<SetPlayerStateCommand>(String("SetPlayerState").toLowerCase());
	commandFactory.registerCommand<SetPublicStateCommand>(String("SetPublicState").toLowerCase());
	commandFactory.registerCommand<SetRankCommand>(String("SetRank").toLowerCase());
	commandFactory.registerCommand<SetRetreatCommand>(String("SetRetreat").toLowerCase());
	commandFactory.registerCommand<SetSecondChanceCommand>(String("SetSecondChance").toLowerCase());
	commandFactory.registerCommand<SetSpeedCommand>(String("SetSpeed").toLowerCase());
	commandFactory.registerCommand<SetSpokenLanguageCommand>(String("SetSpokenLanguage").toLowerCase());
	commandFactory.registerCommand<SetSteadyaimCommand>(String("SetSteadyaim").toLowerCase());
	commandFactory.registerCommand<SetTEFCommand>(String("SetTEF").toLowerCase());
	commandFactory.registerCommand<SetTacticsCommand>(String("SetTactics").toLowerCase());
	commandFactory.registerCommand<SetToughenCommand>(String("SetToughen").toLowerCase());
	commandFactory.registerCommand<SetVerbalAssaultCommand>(String("SetVerbalAssault").toLowerCase());
	commandFactory.registerCommand<SetVeteranRewardCommand>(String("SetVeteranReward").toLowerCase());
	commandFactory.registerCommand<SetWarcryCommand>(String("SetWarcry").toLowerCase());
	commandFactory.registerCommand<SetWaypointActiveStatusCommand>(String("SetWaypointActiveStatus").toLowerCase());
	commandFactory.registerCommand<SetWaypointNameCommand>(String("SetWaypointName").toLowerCase());
	commandFactory.registerCommand<SetpermissionCommand>(String("Setpermission").toLowerCase());
	commandFactory.registerCommand<SetprivacyCommand>(String("Setprivacy").toLowerCase());
	commandFactory.registerCommand<SherKarRageCommand>(String("SherKarRage").toLowerCase());
	commandFactory.registerCommand<ShockCommand>(String("Shock").toLowerCase());
	commandFactory.registerCommand<ShowCouncilRankCommand>(String("ShowCouncilRank").toLowerCase());
	commandFactory.registerCommand<ShowDanceVisualsCommand>(String("ShowDanceVisuals").toLowerCase());
	commandFactory.registerCommand<ShowFactionInformationCommand>(String("ShowFactionInformation").toLowerCase());
	commandFactory.registerCommand<ShowLockoutCommand>(String("ShowLockout").toLowerCase());
	commandFactory.registerCommand<ShowMusicianVisualsCommand>(String("ShowMusicianVisuals").toLowerCase());
	commandFactory.registerCommand<ShowPvPRatingCommand>(String("ShowPvPRating").toLowerCase());
	commandFactory.registerCommand<ShowSpawnRegionCommand>(String("ShowSpawnRegion").toLowerCase());
	commandFactory.registerCommand<SitServerCommand>(String("SitServer").toLowerCase());
	commandFactory.registerCommand<Sk_ShockWaveCommand>(String("Sk_ShockWave").toLowerCase());
	commandFactory.registerCommand<SkillCommand>(String("Skill").toLowerCase());
	commandFactory.registerCommand<SmokebombCommand>(String("Smokebomb").toLowerCase());
	commandFactory.registerCommand<SniperShotCommand>(String("SniperShot").toLowerCase());
	commandFactory.registerCommand<SnoopCommand>(String("Snoop").toLowerCase());
	commandFactory.registerCommand<SocialCommand>(String("Social").toLowerCase());
	commandFactory.registerCommand<SocialInternalCommand>(String("SocialInternal").toLowerCase());
	commandFactory.registerCommand<SpatialChatCommand>(String("SpatialChat").toLowerCase());
	commandFactory.registerCommand<SpatialChatInternalCommand>(String("SpatialChatInternal").toLowerCase());
	commandFactory.registerCommand<SpawnStatusCommand>(String("SpawnStatus").toLowerCase());
	commandFactory.registerCommand<SpinAttackCommand>(String("SpinAttack").toLowerCase());
	commandFactory.registerCommand<SplitCreditsWithGroupCommand>(String("SplitCreditsWithGroup").toLowerCase());
	commandFactory.registerCommand<SpotlightCommand>(String("Spotlight").toLowerCase());
	commandFactory.registerCommand<SprayShotCommand>(String("SprayShot").toLowerCase());
	commandFactory.registerCommand<SquadLeaderCommand>(String("SquadLeader").toLowerCase());
	commandFactory.registerCommand<StabilizersCommand>(String("Stabilizers").toLowerCase());
	commandFactory.registerCommand<StandCommand>(String("Stand").toLowerCase());
	commandFactory.registerCommand<StartBandCommand>(String("StartBand").toLowerCase());
	commandFactory.registerCommand<StartCitySpawnerCommand>(String("StartCitySpawner").toLowerCase());
	commandFactory.registerCommand<StartDanceCommand>(String("StartDance").toLowerCase());
	commandFactory.registerCommand<StartMusicCommand>(String("StartMusic").toLowerCase());
	commandFactory.registerCommand<StartSpawnerCommand>(String("StartSpawner").toLowerCase());
	commandFactory.registerCommand<StartTargetSpawnerCommand>(String("StartTargetSpawner").toLowerCase());
	commandFactory.registerCommand<StartTraceLoggingCommand>(String("StartTraceLogging").toLowerCase());
	commandFactory.registerCommand<StartleShotCommand>(String("StartleShot").toLowerCase());
	commandFactory.registerCommand<StasisCommand>(String("Stasis").toLowerCase());
	commandFactory.registerCommand<StatCommand>(String("Stat").toLowerCase());
	commandFactory.registerCommand<SteadyaimCommand>(String("Steadyaim").toLowerCase());
	commandFactory.registerCommand<StopBandCommand>(String("StopBand").toLowerCase());
	commandFactory.registerCommand<StopBleedingCommand>(String("StopBleeding").toLowerCase());
	commandFactory.registerCommand<StopCitySpawnerCommand>(String("StopCitySpawner").toLowerCase());
	commandFactory.registerCommand<StopCraftingSessionCommand>(String("StopCraftingSession").toLowerCase());
	commandFactory.registerCommand<StopDanceCommand>(String("StopDance").toLowerCase());
	commandFactory.registerCommand<StopMusicCommand>(String("StopMusic").toLowerCase());
	commandFactory.registerCommand<StopSpawnerCommand>(String("StopSpawner").toLowerCase());
	commandFactory.registerCommand<StopTargetSpawnerCommand>(String("StopTargetSpawner").toLowerCase());
	commandFactory.registerCommand<StopTraceLoggingCommand>(String("StopTraceLogging").toLowerCase());
	commandFactory.registerCommand<StoplisteningCommand>(String("Stoplistening").toLowerCase());
	commandFactory.registerCommand<StoppingShotCommand>(String("StoppingShot").toLowerCase());
	commandFactory.registerCommand<StopwatchingCommand>(String("Stopwatching").toLowerCase());
	commandFactory.registerCommand<StructurestatusCommand>(String("Structurestatus").toLowerCase());
	commandFactory.registerCommand<StunAttackCommand>(String("StunAttack").toLowerCase());
	commandFactory.registerCommand<StunRecoveryCommand>(String("StunRecovery").toLowerCase());
	commandFactory.registerCommand<StunningBlowCommand>(String("StunningBlow").toLowerCase());
	commandFactory.registerCommand<SuppressionFireCommand>(String("SuppressionFire").toLowerCase());
	commandFactory.registerCommand<SurrenderSkillCommand>(String("SurrenderSkill").toLowerCase());
	commandFactory.registerCommand<SurveyCommand>(String("Survey").toLowerCase());
	commandFactory.registerCommand<SweepAttackCommand>(String("SweepAttack").toLowerCase());
	commandFactory.registerCommand<SwitchWeaponModeCommand>(String("SwitchWeaponMode").toLowerCase());
	commandFactory.registerCommand<SwordFlurryCommand>(String("SwordFlurry").toLowerCase());
	commandFactory.registerCommand<SynchronizedUiListenCommand>(String("SynchronizedUiListen").toLowerCase());
	commandFactory.registerCommand<SynchronizedUiStopListeningCommand>(String("SynchronizedUiStopListening").toLowerCase());
	commandFactory.registerCommand<SystemMessageCommand>(String("SystemMessage").toLowerCase());
	commandFactory.registerCommand<TacticsCommand>(String("Tactics").toLowerCase());
	commandFactory.registerCommand<TakeCoverCommand>(String("TakeCover").toLowerCase());
	commandFactory.registerCommand<TameCommand>(String("Tame").toLowerCase());
	commandFactory.registerCommand<TargetCommand>(String("Target").toLowerCase());
	commandFactory.registerCommand<TauntCommand>(String("Taunt").toLowerCase());
	commandFactory.registerCommand<TeachCommand>(String("Teach").toLowerCase());
	commandFactory.registerCommand<TeleportCommand>(String("Teleport").toLowerCase());
	commandFactory.registerCommand<TeleportTargetCommand>(String("TeleportTarget").toLowerCase());
	commandFactory.registerCommand<TeleportToCommand>(String("TeleportTo").toLowerCase());
	commandFactory.registerCommand<TellpetCommand>(String("Tellpet").toLowerCase());
	commandFactory.registerCommand<ThrowGrenadeCommand>(String("ThrowGrenade").toLowerCase());
	commandFactory.registerCommand<ThrowTrapCommand>(String("ThrowTrap").toLowerCase());
	commandFactory.registerCommand<ThrowbugGrenadeCommand>(String("ThrowbugGrenade").toLowerCase());
	commandFactory.registerCommand<ThrowcryobanGrenadeCommand>(String("ThrowcryobanGrenade").toLowerCase());
	commandFactory.registerCommand<ThrowfragmentationGrenadeCommand>(String("ThrowfragmentationGrenade").toLowerCase());
	commandFactory.registerCommand<ThrowglopGrenadeCommand>(String("ThrowglopGrenade").toLowerCase());
	commandFactory.registerCommand<Throwimperial_detonatorGrenadeCommand>(String("Throwimperial_detonatorGrenade").toLowerCase());
	commandFactory.registerCommand<ThrowprotonGrenadeCommand>(String("ThrowprotonGrenade").toLowerCase());
	commandFactory.registerCommand<Throwthermal_detonatorGrenadeCommand>(String("Throwthermal_detonatorGrenade").toLowerCase());
	commandFactory.registerCommand<TipCommand>(String("Tip").toLowerCase());
	commandFactory.registerCommand<ToggleAwayFromKeyBoardCommand>(String("ToggleAwayFromKeyBoard").toLowerCase());
	commandFactory.registerCommand<ToggleCombatTauntsCommand>(String("ToggleCombatTaunts").toLowerCase());
	commandFactory.registerCommand<ToggleDisplayingFactionRankCommand>(String("ToggleDisplayingFactionRank").toLowerCase());
	commandFactory.registerCommand<TorsoShotCommand>(String("TorsoShot").toLowerCase());
	commandFactory.registerCommand<TotalHealCommand>(String("TotalHeal").toLowerCase());
	commandFactory.registerCommand<ToughenCommand>(String("Toughen").toLowerCase());
	commandFactory.registerCommand<TrainPetCommand>(String("TrainPet").toLowerCase());
	commandFactory.registerCommand<TransferForceCommand>(String("TransferForce").toLowerCase());
	commandFactory.registerCommand<TransferItemArmorCommand>(String("TransferItemArmor").toLowerCase());
	commandFactory.registerCommand<TransferItemCommand>(String("TransferItem").toLowerCase());
	commandFactory.registerCommand<TransferItemMiscCommand>(String("TransferItemMisc").toLowerCase());
	commandFactory.registerCommand<TransferItemWeaponCommand>(String("TransferItemWeapon").toLowerCase());
	commandFactory.registerCommand<TransferstructureCommand>(String("Transferstructure").toLowerCase());
	commandFactory.registerCommand<TraumatizeCommand>(String("Traumatize").toLowerCase());
	commandFactory.registerCommand<TumbleToKneelingCommand>(String("TumbleToKneeling").toLowerCase());
	commandFactory.registerCommand<TumbleToProneCommand>(String("TumbleToProne").toLowerCase());
	commandFactory.registerCommand<TumbleToStandingCommand>(String("TumbleToStanding").toLowerCase());
	commandFactory.registerCommand<TurretFireCommand>(String("TurretFire").toLowerCase());
	commandFactory.registerCommand<TurretFireManualCommand>(String("TurretFireManual").toLowerCase());
	commandFactory.registerCommand<TurretShotCommand>(String("TurretShot").toLowerCase());
	commandFactory.registerCommand<UnCityBanCommand>(String("UnCityBan").toLowerCase());
	commandFactory.registerCommand<UnassociateDroidControlDeviceWithShipCommand>(String("UnassociateDroidControlDeviceWithShip").toLowerCase());
	commandFactory.registerCommand<UnconsentCommand>(String("Unconsent").toLowerCase());
	commandFactory.registerCommand<UnderHandShotCommand>(String("UnderHandShot").toLowerCase());
	commandFactory.registerCommand<UndockCommand>(String("Undock").toLowerCase());
	commandFactory.registerCommand<UnfreezePlayerCommand>(String("UnfreezePlayer").toLowerCase());
	commandFactory.registerCommand<UninstallShipComponentCommand>(String("UninstallShipComponent").toLowerCase());
	commandFactory.registerCommand<UninviteCommand>(String("Uninvite").toLowerCase());
	commandFactory.registerCommand<UnpilotShipCommand>(String("UnpilotShip").toLowerCase());
	commandFactory.registerCommand<UnsnoopCommand>(String("Unsnoop").toLowerCase());
	commandFactory.registerCommand<UnstickCommand>(String("Unstick").toLowerCase());
	commandFactory.registerCommand<UseDoctorBagCommand>(String("UseDoctorBag").toLowerCase());
	commandFactory.registerCommand<UseReconDroneCommand>(String("UseReconDrone").toLowerCase());
	commandFactory.registerCommand<UseSkillBuffCommand>(String("UseSkillBuff").toLowerCase());
	commandFactory.registerCommand<VentriloquismCommand>(String("Ventriloquism").toLowerCase());
	commandFactory.registerCommand<VerbalAssaultCommand>(String("VerbalAssault").toLowerCase());
	commandFactory.registerCommand<VertFurnitureCommand>(String("VertFurniture").toLowerCase());
	commandFactory.registerCommand<VitalizeCommand>(String("Vitalize").toLowerCase());
	commandFactory.registerCommand<VolleyFireAttackCommand>(String("VolleyFireAttack").toLowerCase());
	commandFactory.registerCommand<VolleyFireCommand>(String("VolleyFire").toLowerCase());
	commandFactory.registerCommand<VrepairCommand>(String("Vrepair").toLowerCase());
	commandFactory.registerCommand<VrepairotherCommand>(String("Vrepairother").toLowerCase());
	commandFactory.registerCommand<WarcryCommand>(String("Warcry").toLowerCase());
	commandFactory.registerCommand<WarningShotCommand>(String("WarningShot").toLowerCase());
	commandFactory.registerCommand<WatchCommand>(String("Watch").toLowerCase());
	commandFactory.registerCommand<WaypointCommand>(String("Waypoint").toLowerCase());
	commandFactory.registerCommand<WipeItemsCommand>(String("WipeItems").toLowerCase());
	commandFactory.registerCommand<WookieeRoarCommand>(String("WookieeRoar").toLowerCase());
	*/
}
