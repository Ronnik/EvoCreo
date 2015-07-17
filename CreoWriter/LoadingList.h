/*
These lists hold all creo, moves, abilities, traits, etc. that are loaded into memory so that each one only has to be loaded once.
They don't load an item until it's requested, and they store it for the lifetime of the list.
They only give out constant references so that they never have to copy data, and so the data in the list cannot be modified.
*/

#include <vector>
#include "Creo.h"
#include "Move.h"

using std::vector;

#ifndef LOADINGLIST_H
#define LOADINGLIST_H



template <typename T>
class LoadingList
{
protected:
	vector<T> loadedList;

	T* preload(const string& name);
		//Checks the list for an object with that name. If it finds one, it returns a pointer to it.
		//If it doesn't find one, it adds an object with that name to the list and returns a pointer to it.
		//Using this function prevents having two items on the list with the same name.
		//It also allows for objects that were not fully loaded to be filled later, perhaps from a different file.

public:
	LoadingList() {vector<const T> loadedList = vector<const T>();}
		//creates an empty list

	virtual void load(const string& name = "");
		//loads specified item and adds it to the list
		//leave blank to load all unloaded items

	const T& get(const string& name);
		//Checks the list to see if the requested Creo is on it. If it is, it returns a constant reference to it.
		//If it's not on the list, it loads it from the data and strings files, adds it to the list, and returns a constant reference.

	vector<const T&> getAllLoaded() const;
		//returns a vector containing constant references to all items loaded in the list

	vector<const T&> getAll();
		//loads all unloaded items from the data and strings files, adds them to the list,
		//and returns a vector containing references to all items in the list
};


class CreoList: public LoadingList<Creo>
{
	string dataFileName,
		stringsFileName;

public:
	CreoList(const string& dataFileNameArg, const string& stringsFileNameArg)
	{dataFileName = dataFileNameArg; stringsFileName = stringsFileNameArg;}
		//assigns the file names but does not open the files

	void setDataFileName(const string& newDataFileName) {dataFileName = newDataFileName;}
		//Used to change the data file to load additional items. Does not affect the loaded list.
	void setStringsFileName(const string& newStringsFileName) {stringsFileName = newStringsFileName;}
		//Used to change the strings file to load additional items. Does not affect the loaded list.

	void load(const string& name = "");
		//Speicalized for loading Creo from "CreoData.xml" and "CreoStrings.xml"
		//opens and closes data and strings files
};


class MoveList: public LoadingList<Move>
{
	string dataFileName,
		stringsFileName;

public:
	MoveList(const string& dataFileNameArg, const string& stringsFileNameArg)
	{dataFileName = dataFileNameArg; stringsFileName = stringsFileNameArg;}
		//assigns the file names but does not open the files

	void setDataFileName(const string& newDataFileName) {dataFileName = newDataFileName;}
		//Used to change the data file to load additional items. Does not affect the loaded list.
	void setStringsFileName(const string& newStringsFileName) {stringsFileName = newStringsFileName;}
		//Used to change the strings file to load additional items. Does not affect the loaded list.

	void load(const string& name = "");
		//Speicalized for loading Creo from "MoveData.xml" and "MoveStrings.xml"
		//opens and closes data and strings files
};


class TraitList: public LoadingList<Trait>
{
	string stringsFileName;

public:
	TraitList(const string& stringsFileNameArg) {stringsFileName = stringsFileNameArg;}
		//assigns the file name but does not open the file

	void setStringsFileName(const string& newStringsFileName) {stringsFileName = newStringsFileName;}
		//Used to change the strings file to load additional items. Does not affect the loaded list.

	void load(const string& name = "");
		//Speicalized for loading Traits from "SceneStrings.xml"
		//opens and closes strings file
};


class AbilityList: public LoadingList<Ability>
{
	string stringsFileName;

public:
	AbilityList(const string& stringsFileNameArg) {stringsFileName = stringsFileNameArg;}
		//assigns the file name but does not open the file

	void setStringsFileName(const string& newStringsFileName) {stringsFileName = newStringsFileName;}
		//Used to change the strings file to load additional items. Does not affect the loaded list.

	void load(const string& name = "");
		//Speicalized for loading Abilities from "SceneStrings.xml"
		//opens and closes strings file
};

#endif