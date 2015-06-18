object_draft_schematic_armor_armor_appearance_assault_trooper_helmet = object_draft_schematic_armor_shared_armor_appearance_assault_trooper_helmet:new {

   templateType = DRAFTSCHEMATIC,

   customObjectName = "Assault Trooper Armor Helmet",

   craftingToolTab = 2, -- (See DraftSchemticImplementation.h)
   complexity = 15, 
   size = 3, 

   xpType = "crafting_clothing_armor", 
   xp = 260, 

   assemblySkill = "armor_assembly", 
   experimentingSkill = "armor_experimentation", 
   customizationSkill = "armor_customization", 

   customizationOptions = {2, 1},
   customizationStringNames = {"/private/index_color_1", "/private/index_color_2"},
   customizationDefaults = {117, 159},

  ingredientTemplateNames = {"craft_clothing_ingredients_n", "craft_clothing_ingredients_n", "craft_clothing_ingredients_n", "craft_clothing_ingredients_n", "craft_clothing_ingredients_n", "craft_clothing_ingredients_n", "craft_clothing_ingredients_n", "craft_clothing_ingredients_n", "craft_clothing_ingredients_n"},
   ingredientTitleNames = {"auxilary_coverage", "body", "liner", "hardware_and_attachments", "binding_and_reinforcement", "padding", "armor", "load_bearing_harness", "reinforcement"},
   ingredientSlotType = {0, 0, 0, 0, 0, 0, 1, 1, 1},
   resourceTypes = {"ore_intrusive", "fuel_petrochem_solid_known", "fiberplast_naboo", "aluminum", "copper_beyrllius", "hide_wooly", "object/tangible/component/armor/shared_armor_segment_composite.iff", "object/tangible/component/clothing/shared_synthetic_cloth.iff", "object/tangible/component/clothing/shared_reinforced_fiber_panels.iff"},
   resourceQuantities = {70, 70, 35, 40, 30, 30, 3, 1, 1},
   contribution = {100, 100, 100, 100, 100, 100, 100, 100, 100},


   targetTemplate = "object/tangible/wearables/armor/assault_trooper/armor_assault_trooper_helmet.iff",

   additionalTemplates = {
             }

}
ObjectTemplates:addTemplate(object_draft_schematic_armor_armor_appearance_assault_trooper_helmet, "object/draft_schematic/armor/armor_appearance_assault_trooper_helmet.iff")
