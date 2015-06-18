ForceLightningCommand = {
        name = "forcelightning",
	combatSpam = "forcelightning",
	animationCRC = hashCode("force_lightning_1_particle_level_3_light"),
	accuracySkillMod = "forcelightning_accuracy";

	poolsToDamage = HEALTH_ATTRIBUTE,
	attackType = FORCEATTACK,

	damage = 800,
	forceCost = 175,
	actionCostMultiplier = 1.25,

	stateEffects = {
	  StateEffect( 
		STUN_EFFECT, 
		{}, 
		{}, 
		{ "jedi_state_defense" }, 
		30, 
		100, 
		10 
	  )
	},

	range = 32
}

AddCommand(ForceLightningCommand)
