// *** Evolution ***
// Contains pointer of Creo that the current Creo can evolve into, plus the evolution type and the level or element
// Creo uses a vector of these to store all possible evolutions

// *** LearnedSkill ***
// Template class for holding a move/trait/ability and the level it is learned
// Also includes string for tome name for Moves
// Creo uses vectors of LearnedSkills of types Move, Trait, and Ability

// *** Creo ***
// Struct for storing data for one Creo
// Can load data from data file and strings (description) from strings file

#ifndef CREO_H
#define CREO_H

#include <string>
#include <vector>
#include <stack>
#include "Move.h"

using std::string;
using std::vector;
using std::stack;



struct Evolution;



template <typename T>
struct LearnedSkill
{
	const T* info;

	int levelLearned;

	string tomeName;

	LearnedSkill(const T* skill, const int level = 0, const string& tome = "")
	{info = skill; levelLearned = level; tomeName = tome;}
};



struct Creo
{
	string name,					//creo name
		description,				//creopedia description
		element1,					//primary element
		element2,					//secondary element
		creoClass,					//creo Class (what you see when you touch a creo's name in battle)
		rarity,						//"COMMON", "UNCOMMON", "RARE", "ASCENDENT", or "PRIME"
		levelUpSpeed;				//"SLOW", "MEDIUM_SLOW", "STANDARD", "MEDIUM_FAST", or "FAST"

	int id,							//creopedia number
		vitality,					//vitality base stat
		attack,						//physical attack base stat
		special,					//special (elemental) attack base stat
		speed,						//speed base stat
		defense,					//defense base stat
		catchRate,					//number from 0-250, 0 being hardest to catch
		exp,						//I think this is how much EXP is gained from defeating the creo (creo or player EXP, not sure)
		runChance;					//number from 0-3

	float weight,					//weight in kg
		size;						//size in m

	// ** All moves, traits, and abilities are loaded into the vectors in the order they are written in the file,
	// ** but in the file they should always be written in order of increasing level.
	vector<LearnedSkill<Move>> eliteMoves,		//move and level learned - LearnedMove inherits data from Move struct
		normalMoves,
		healingMoves;

	vector<LearnedSkill<Trait>> traits;			//trait and level learned - LearnedTrait inherits data from Trait struct

	vector<LearnedSkill<Ability>> abilities;	//ability and level learned - LearnedAbility inherits data from Ability struct

	vector<const Move*> tomeMoves;
	/*	TOME MOVES ORDER
		0	Tome of Normality
		1	Tome of Fire
		2	Tome of Water
		3	Tome of Air
		4	Tome of Earth
		5	Tome of Nature
		6	Tome of Electricity
		7	Tome of Light
		8	Tome of Darkness
		9	ELITE TOME #1: Creo's Primary Element ('element1') (should always exist)
		10	ELITE TOME #2: Creo's Secondary Element ('element2') (does NOT exist if element1 == element2)
	*/

	vector<Evolution> evolutions;		//stores all the creo's evolutions (subsequent stage only)
	const Creo* previousStage;			//the creo that evolves into this one
		// ** NOTE: Currently, each creo's data only says what creos it can evolve into, not what it evolves from.
		// ** This means that even if a creo has a previous evolution, it will NOT be pointed to here unless that creo is loaded!
		// ** Another note: loading a creo will also load all of its evolutions. Side effect: loading a pre-evolution creo after...
		// ** ...its evolved form will automatically point its 'previousStage' to the pre-evolved creo.
	
	Creo(const string& nameArg = "", const string& descriptionArg = "", const string& element1Arg = "", const string& element2Arg = "", const string& creoClassArg = "", const string& rarityArg = "", const string& levelUpSpeedArg = "", const int vitalityArg = 0, const int attackArg = 0, const int specialArg = 0, const int speedArg = 0, const int defenseArg = 0, const int catchRateArg = 0, const int expArg = 0, const int runChanceArg = 0, const float weightArg = 0.0, const float sizeArg = 0.0, const vector<LearnedSkill<Move>>& eliteMovesArg = vector<LearnedSkill<Move>>(), const vector<LearnedSkill<Move>>& normalMovesArg = vector<LearnedSkill<Move>>(), const vector<LearnedSkill<Move>>& healingMovesArg = vector<LearnedSkill<Move>>(), const vector<LearnedSkill<Trait>>& traitsArg = vector<LearnedSkill<Trait>>(), const vector<LearnedSkill<Ability>>& abilitiesArg = vector<LearnedSkill<Ability>>(), const vector<const Move*>& tomeMovesArg = vector<const Move*>(), const vector<Evolution>& evolutionsArg = vector<Evolution>(), const Creo* previousStageArg = NULL);
		//Constructor creates an empty Creo by default. CreoList fills in data when loading from file.

	void writeWikiaPage(string filename = "") const;
		//writes the wikia page for the Creo and saves it as a .txt file (default name is the creo's id number + "_" + name + ".txt")
		//The resulting text file is wikia source text.
		//The template is hard-coded, so to change it you must change this function.

	string getFormattedEvolutionTree(stack<string> branches = stack<string>()) const;
		//creates an evolution tree using all previous and subsequent evolution stages (formatted as wikia source code)
		//String stack is used internally to specify which branches of the tree are generated.
		//(ignores offshoots of lower stages for higher stage creos)
	string getFormattedMovesTable(const vector<LearnedSkill<Move>>& movesVector) const;
		//creates a table of all the moves in the given vector (formatted as wikia source code)
	string getFormattedTomeMovesTable() const;
			//creates a table of all the moves taught by tomes (formatted as wikia source code)
};



struct Evolution
{
	const Creo* creo;	//creo that the current creo will evolve into
		
	int type,			//Currently 2 types of evolution - 0:Level, 1:Elemental
		level;			//level at which creo evolves; if type == 1, level == 0
		
	string element;		//element for which the creo needs affinity to evolve; if type == 0, element == -1

	Evolution(const Creo* evolvedCreo, const int evolutionLevel);
		//This creates a type 0 Evolution.
	Evolution(const Creo* evolvedCreo, const string& evolutionElement);
		//This creates a type 1 Evolution.
};

#endif