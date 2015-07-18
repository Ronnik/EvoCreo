/*
These lists hold all creo, moves, abilities, traits, etc. that are loaded into memory so that each one only has to be loaded once.
They don't load an item until it's requested, and they store it for the lifetime of the list.
They only give out constant references so that they never have to copy data, and so the data in the list cannot be modified.
*/

#include <string>
#include <vector>
#include "Creo.h"
#include "Move.h"
#include "Effect.h"

using std::string;
using std::vector;

#ifndef CREOLOADER_H
#define CREOLOADER_H

class CreoLoader
{
	vector<Creo*> creoList;
	vector<Move*> moveList;
	vector<Trait*> traitList;
	vector<Ability*> abilityList;
	vector<Effect*> effectList;
	vector<Condition*> conditionList;
	vector<Boon*> boonList;

	string creoDataFilename,		//"CreoData.xml" contains creo data
		creoStringsFilename,		//"CreoStrings.xml" contains creo strings
		moveDataFilename,			//"MoveData.xml" contains move data
		moveStringsFilename,		//"MoveStrings.xml" contains move strings
		sceneStringsFilename;		//"SceneStrings.xml" contains strings for traits and abilities

	template <typename T>
	T* preload(vector<T*>& list, const string& name);
		//Checks the list for an object with that name. If it finds one, it returns a pointer to it.
		//If it doesn't find one, it adds an object with that name to the list and returns a pointer to it.
		//Using this function prevents having two items on the list with the same name.
		//It also allows for objects that were not fully loaded to be filled later, perhaps from a different file.

	template <typename T>
	T* get(const string& name, vector<T*>& list);
		//template for other, class-specific get functions (such as getCreo)
		//does not load, only returns a pointer to an item already on the list
		//if item is not on list, returns NULL

public:
	CreoLoader(const string& creoDataFilenameArg = "CreoData.xml", const string& creoStringsFilenameArg = "CreoStrings.xml", const string& moveDataFilenameArg = "MoveData.xml", const string& moveStringsFilenameArg = "MoveStrings.xml", const string& sceneStringsFilenameArg = "SceneStrings.xml");
		//creates empty lists
		//does not open any of the files, only load functions do that

	~CreoLoader();
		//goes through all the lists and deallocates the memory for each item

	//These functions only change the file names. They do not open the files or change the lists.
	void setCreoDataFilename(const string& newCreoDataFilename) {creoDataFilename = newCreoDataFilename;}
	void setCreoStringsFilename(const string& newCreoStringsFilename) {creoStringsFilename = newCreoStringsFilename;}
	void setMoveDataFilename(const string& newMoveDataFilename) {moveDataFilename = newMoveDataFilename;}
	void setMoveStringsFilename(const string& newMoveStringsFilename) {moveStringsFilename = newMoveStringsFilename;}
	void setSceneStringsFilename(const string& newSceneStringsFilename) {sceneStringsFilename = newSceneStringsFilename;}

	//Load functions will never create duplicate items. If an item is already in the list, they will write over existing data.
	void loadCreo(const string& name = "");
		//loads the creo with the given name
		//if no name is given, loads all creo from files
	void loadMove(const string& name = "");
		//loads the move with the given name
		//if no name is given, loads all moves from files
	void loadTrait(const string& name = "");
		//loads the trait with the given name
		//if no name is given, loads all traits from file
	void loadAbility(const string& name = "");
		//loads the ability with the given name
		//if no name is given, loads all abilities from file
	void loadEffect(const string& name);
		//"loads" the effect with the given name
		//effects are not stored on file, so just puts the name in an Effect and adds it to the list
	void loadCondition(const string& name = "");
		//loads the condition with the given name
		//if no name is given, loads all conditions from file
	void loadBoon(const string& name = "");
		//loads the boon with the given name
		// if no name is given, loads all conditions from file
	void loadAll();
		//loads all items from the files (creo, moves, traits, and abilities)

	const Creo* getCreo(const string& name);
	const Move* getMove(const string& name);
	const Trait* getTrait(const string& name);
	const Ability* getAbility(const string& name);
	const Effect* getEffect(const string& name);
	const Condition* getCondition(const string& name);
	const Boon* getBoon(const string& name);
		//Checks the list to see if the requested item is on it. If it is, it returns a constant reference to it.
		//If it's not on the list, it loads it from the data and strings files, adds it to the list, and returns a constant reference.

	vector<const Creo*> getAllCreo(bool loadAll = true);
	vector<const Move*> getAllMoves(bool loadAll = true);
	vector<const Trait*> getAllTraits(bool loadAll = true);
	vector<const Ability*> getAllAbilities(bool loadAll = true);
	vector<const Effect*> getAllEffects();		//Only returns "loaded" effects, since effects are not written in the files.
	vector<const Condition*> getAllConditions(bool loadAll = true);
	vector<const Boon*> getAllBoons(bool loadAll = true);
		//returns a vector with all loaded items of the specified type
		//if 'loadAll' is true, loads all items of that type first
		//if 'loadAll' is false, only returns already loaded items
};

#endif