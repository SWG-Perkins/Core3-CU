MeleeStrikeCommand = {
        name = "meleestrike",

	damageMultiplier = 1.1,
	speedMultiplier = 1.5,

	actionCostMultiplier = 1.0,
	mindCostMultiplier = 0.2,

	animationCRC = hashCode(""),
	combatSpam = "meleestrike",
	poolsToDamage = HEALTH_ATTRIBUTE,

	range = 5
}

AddCommand(MeleeStrikeCommand)
