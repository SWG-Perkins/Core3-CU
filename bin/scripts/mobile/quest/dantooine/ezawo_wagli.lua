ezawo_wagli = Creature:new {
	objectName = "",
	customName = "Ezawo Wagli",
	socialGroup = "thug",
	faction = "thug",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = KILLER,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {
				"object/mobile/dressed_criminal_thug_aqualish_male_01.iff",
				"object/mobile/dressed_criminal_thug_aqualish_male_02.iff",
				"object/mobile/dressed_criminal_thug_bothan_male_01.iff",
				"object/mobile/dressed_criminal_thug_human_male_01.iff",
				"object/mobile/dressed_criminal_thug_human_male_02.iff",
				"object/mobile/dressed_criminal_thug_rodian_male_01.iff",
				"object/mobile/dressed_criminal_thug_trandoshan_male_01.iff",
				"object/mobile/dressed_criminal_thug_zabrak_male_01.iff"}, 	
	lootGroups = {},
	weapons = {},
	conversationTemplate = "xaan_talmaron_mission_target_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(ezawo_wagli, "ezawo_wagli")