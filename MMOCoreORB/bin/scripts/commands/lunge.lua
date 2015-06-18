LungeCommand = {
        name = "lunge",

	damageMultiplier = 0.8,
	speedMultiplier = 1.5,

	actionCostMultiplier = 1.5,
	mindCostMultiplier = 0.2,

	animationCRC = hashCode(""),
	combatSpam = "lunge",
	poolsToDamage = HEALTH_ATTRIBUTE,

	range = 15
}

AddCommand(LungeCommand)
