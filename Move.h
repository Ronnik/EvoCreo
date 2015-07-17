// *** ChanceEffect ***
// Basic Struct for storing the ID of an effect/condition/boon and the chance of it occurring when a move hits 

// *** Move ***
// Struct for storing data for one Move
// Can load data from data file and strings (description) from strings file

// *** Trait ***
// Stores name, description, and ID of one Trait
// Can load strings from Strings file

// *** Ability ***
// Stores name, description, and ID of one Ability
//Can load strings from Strings file

#include <string>
#include <vector>

using std::string;
using std::vector;

#ifndef MOVE_H
#define MOVE_H



struct ChanceEffect
{
	string name;

	float chance;		//ranges from 0.0 to 1.0

	ChanceEffect(const string& effectName, const float effectChance);	//assigns 'effectName' to 'name' and 'effectChance' to 'chance'
};



struct Move
{
	string name,			//move name
		description,		//move description
		type,				//PHYSICAL, SPECIAL, or EFFECT
		element,			//move element
		moveClass,			//This is either a hidden or unused value, not sure.
		contactType,		//This is either a hidden or unused value, not sure.
		skillType;			//ELITE, NORMAL, or HEALING

	float accuracy;			//Accuracy, 0.0 - 1.0, shown as 0 - 100 in game

	int damage,		//Ranges from 10 to 150, so not exactly the same as Power. There's no Power value, so Power must be derived from this somehow.
		recharge;			//Recharge time, in turns.

	vector<ChanceEffect> effects,	//I think effects are things like Surge (not conditions or boons but still applied every turn)
		conditions,					//Conditions, such as Burn and Poison
		boons;						//Boons, such as Agility and Regen

	Move(const string& nameArg = "", const string& descriptionArg = "", const string& typeArg = "", const string& elementArg = "", const string& moveClassArg = "", const string& contactTypeArg = "", const string& skillTypeArg = "NORMAL", const float accuracyArg = 1.0, const int damageArg = 0, const int rechargeArg = 0, const vector<ChanceEffect> effectsArg = vector<ChanceEffect>(), const vector<ChanceEffect> conditionsArg = vector<ChanceEffect>(), const vector<ChanceEffect> boonsArg = vector<ChanceEffect>());
		//Constructor creates an empty Move. MoveList fills in data when loading from file.
};



struct Trait
{
	string name,		//trait name
		description;	//trait description

	Trait(string nameArg = "", string descriptionArg = "")
	{name = nameArg; description = descriptionArg;}
		//TraitList fills in data when loading from file.
};

// ** Trait and Ability structs are identical except for name, but I separated them in case there's a difference later.

struct Ability
{
	string name,		//ability name
		description;	//ability description

	Ability(string nameArg = "", string descriptionArg = "")
	{name = nameArg; description = descriptionArg;}
		//AbilityList fills in data when loading from file.
};



#endif