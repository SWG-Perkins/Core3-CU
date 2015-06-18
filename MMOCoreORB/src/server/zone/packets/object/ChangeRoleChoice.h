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

#ifndef CHANGEROLECHOICECALLBACK_H_
#define CHANGEROLECHOICECALLBACK_H_

#include "ObjectControllerMessageCallback.h"

class ChangeRoleChoiceCallback : public MessageCallback {
	int icon;

	ObjectControllerMessageCallback* objectControllerMain;

	VectorMap<int, String> professionsVector;

public:
	ChangeRoleChoiceCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;

		icon = 0;

		professionsVector.put(0, "crafting_artisan_novice");
		professionsVector.put(5, "social_entertainer_novice");
		professionsVector.put(10, "science_medic_novice");
		professionsVector.put(15, "science_doctor_novice");
		professionsVector.put(15, "science_combatmedic_novice");
		professionsVector.put(20, "outdoors_scout_novice");
		professionsVector.put(20, "outdoors_squadleader_novice");
		professionsVector.put(30, "combat_marksman_novice");
		professionsVector.put(35, "combat_rifleman_novice");
		professionsVector.put(35, "combat_commando_novice");
		professionsVector.put(40, "combat_pistol_novice");
		professionsVector.put(40, "combat_carbine_novice");
		professionsVector.put(40, "combat_smuggler_novice");
		professionsVector.put(50, "combat_brawler_novice");
		professionsVector.put(55, "combat_1hsword_novice");
		professionsVector.put(55, "combat_2hsword_novice");
		professionsVector.put(60,"combat_unarmed_novice");
		professionsVector.put(65, "combat_polearm_novice");
		professionsVector.put(65, "combat_bountyhunter_novice");
		professionsVector.put(70, "force_discipline_light_saber_novice");
		professionsVector.put(75, "force_discipline_powers_novice");
		professionsVector.put(80, "force_discipline_healing_novice");
		professionsVector.put(85, "force_discipline_enhancements_novice");
		professionsVector.put(90, "force_discipline_defender_novice");
		professionsVector.put(95, "crafting_architect_novice");
		professionsVector.put(95, "crafting_armorsmith_novice");
		professionsVector.put(95, "crafting_chef_novice");
		professionsVector.put(95, "crafting_droidengineer_novice");
		professionsVector.put(95, "crafting_shipwrite_novice");
		professionsVector.put(95, "crafting_tailor_novice");
		professionsVector.put(95, "crafting_weaponsmith_novice");
		professionsVector.put(100, "social_dancer_novice");
		professionsVector.put(100, "social_musician_novice");
	}

	void parse(Message* message) {
		icon = message->parseInt();
	}

	void run() {
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( client->getPlayer().get().get());

		if (player == NULL)
			return;

		for (int i = (player->getRoleIconIndex() / 5); i < professionsVector.size(); ++i) {
			if (!player->hasSkill(professionsVector.elementAt(i).getValue())) {
				continue;
			}

			player->setRoleIconIndex(professionsVector.elementAt(i).getKey());
			return;
		}

	}
};

#endif /*COMMANDTIMER_H_*/
