MeleeHitCommand = {
        name = "meleehit",

	damageMultiplier = 1.0,
	speedMultiplier = 1.5,

	actionCostMultiplier = 2.0,
	mindCostMultiplier = 0.2,

	animationCRC = hashCode(""),
	combatSpam = "meleehit",
	poolsToDamage = HEALTH_ATTRIBUTE,

	range = 5
}

AddCommand(MeleeHitCommand)
