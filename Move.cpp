#include <iostream>
#include "Move.h"

using std::cout;

ChanceEffect::ChanceEffect(const string& effectName, const float effectChance)
{
	name = effectName;
	chance = effectChance;
}



Move::Move(const string& nameArg, const string& descriptionArg, const string& typeArg, const string& elementArg, const string& moveClassArg, const string& contactTypeArg, const string& skillTypeArg, const float accuracyArg, const int damageArg, const int rechargeArg, const vector<ChanceEffect> effectsArg, const vector<ChanceEffect> conditionsArg, const vector<ChanceEffect> boonsArg)
{
	name = nameArg;
	description = descriptionArg;
	type = typeArg;
	element = elementArg;
	moveClass = moveClassArg;
	contactType = contactTypeArg;
	skillType = skillTypeArg;

	accuracy = accuracyArg;

	damage = damageArg;
	recharge = rechargeArg;

	effects = effectsArg;
	conditions = conditionsArg;
	boons = boonsArg;
}