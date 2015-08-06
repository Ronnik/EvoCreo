// *** Condition ***
// Stores name and description of one Condition
//Can load strings from SceneStrings.xml

// *** Boon ***
// Stores name and description of one Boon
//Can load strings from SceneStrings.xml

#ifndef EFFECT_H
#define EFFECT_H

#include <string>

using std::string;



struct Effect
{
	string name,
		description;
	//Effects don't have in-game descriptions, but if someone writes them they can be accommodated.

	Effect(const string& nameArg = "", const string& descriptionArg = "")
	{name = nameArg; description = descriptionArg;}
};

struct Condition
{
	string name,		//condition name
		description;	//boon description

	Condition(const string& nameArg = "", const string& descriptionArg = "")
	{name = nameArg; description = descriptionArg;}
		//ConditionList fills in data when loading from file.
};

struct Boon
{
	string name,		//boon name
		description;	//boon description

	Boon(const string& nameArg = "", const string& descriptionArg = "")
	{name = nameArg; description = descriptionArg;}
		//BoonList fills in data when loading from file.
};

#endif