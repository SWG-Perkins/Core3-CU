ChargeShotCommand = {
	name = "chargeshot",
	damageMultiplier = 1.5,
	actionCostMultiplier = 16,
	mindCostMultiplier = 2,

	animationCRC = hashCode("charge"),

	combatSpam = "chargeblast",

	stateEffects = {
	  StateEffect( 
		KNOCKDOWN_EFFECT, 
		{ "knockdownRecovery", "lastKnockdown" }, 
		{ "knockdown_defense" }, 
		{}, 
		40, 
		100, 
		0 
	  )
	},


	poolsToDamage = HEALTH_ATTRIBUTE,



	range = -1


}
AddCommand(ChargeShotCommand)
