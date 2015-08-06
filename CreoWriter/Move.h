// *** LearnedSkill ***
// Template class for holding a move/trait/ability and the level it is learned
// Also includes string for tome name for Moves
// Move uses a vector of LearnedSkills to know which Creo can learn the Move
// Creo uses vectors of LearnedSkills of types Move, Trait, and Ability

// *** ChanceEffect ***
// Basic Struct for storing an effect/condition/boon and the chance of it occurring when a move hits 

// *** Move ***
// Struct for storing data for one Move
// Can load data from data file and strings (description) from strings file

// *** Trait ***
// Stores name and description of one Trait
// Can load strings from Strings file

// *** Ability ***
// Stores name and description of one Ability
//Can load strings from Strings file

#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <vector>
#include "Effect.h"

using std::string;
using std::vector;



struct Creo;

template <typename T>
struct LearnedSkill
{
	const T* info;

	int levelLearned;

	string tomeName;

	LearnedSkill(const T* skill, const int level)
	{info = skill; levelLearned = level; tomeName = "";}

	LearnedSkill(const T* skill, const string& tome)
	{info = skill; levelLearned = 0; tomeName = tome;}

	LearnedSkill(const T* skill = NULL)
	{info = skill; levelLearned = 0; tomeName = "";}

	LearnedSkill(const int level)
	{info = NULL; levelLearned = level; tomeName = "";}

	LearnedSkill(const string& tome)
	{info = NULL; levelLearned = 0; tomeName = tome;}
};



template <typename T>
struct ChanceEffect
{
	const T* info;

	float chance;		//ranges from 0.0 to 1.0

	ChanceEffect(const T* effect, const float effectChance)
	{info = effect; chance = effectChance;}
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

	int power,				//Called "basedamage" in the data file
		recharge;			//Recharge time, in turns.

	vector<ChanceEffect<Effect>> effects;			//I think effects are things like Surge (not conditions or boons but still applied every turn)
	vector<ChanceEffect<Condition>> conditions;		//Conditions, such as Burn and Poison
	vector<ChanceEffect<Boon>> boons;				//Boons, such as Agility and Regen

	vector<LearnedSkill<Creo>> creoLearn;	//Creo that can learn this move by levelling up or by tome

	Move(const string& nameArg = "", const string& descriptionArg = "", const string& typeArg = "", const string& elementArg = "", const string& moveClassArg = "", const string& contactTypeArg = "", const string& skillTypeArg = "NORMAL", const float accuracyArg = 1.0, const int powerArg = 0, const int rechargeArg = 0, const vector<ChanceEffect<Effect>> effectsArg = vector<ChanceEffect<Effect>>(), const vector<ChanceEffect<Condition>> conditionsArg = vector<ChanceEffect<Condition>>(), const vector<ChanceEffect<Boon>> boonsArg = vector<ChanceEffect<Boon>>(), vector<LearnedSkill<Creo>> creoLearnArg = vector<LearnedSkill<Creo>>());
		//Constructor creates an empty Move. MoveList fills in data when loading from file.

	void writeWikiaPage(string filename = "") const;
		//writes the wikia page for the Move and saves it as a .txt file (default name is the move's name + ".txt")
		//The resulting text file is wikia source text.
		//The template is hard-coded, so to change it you must change this function.
};



struct Trait
{
	string name,		//trait name
		description;	//trait description

	Trait(const string& nameArg = "", const string& descriptionArg = "")
	{name = nameArg; description = descriptionArg;}
		//TraitList fills in data when loading from file.
};

// ** Trait and Ability structs are identical except for name, but I separated them in case there's a difference later.

struct Ability
{
	string name,		//ability name
		description;	//ability description

	Ability(const string& nameArg = "", const string& descriptionArg = "")
	{name = nameArg; description = descriptionArg;}
		//AbilityList fills in data when loading from file.
};



#endif