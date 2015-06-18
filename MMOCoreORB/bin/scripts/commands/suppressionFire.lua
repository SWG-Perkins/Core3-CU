SuppressionFireCommand = {
        name = "suppresionfire",

	damageMultiplier = 0.4,
	actionCostMultiplier = 18.0,
	mindCostMultiplier = 4.0,

	poolsToDamage = HEALTH_ATTRIBUTE,

	animationCRC = hashCode("fire_3_special_single_light_face"),

	coneAngle = 45,
	coneAction = true,

	combatSpam = "suppressionfire",

	range = -1
}

AddCommand(SuppressionFireCommand)
