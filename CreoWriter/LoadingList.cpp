#include <iostream>
#include <vector>
#include <fstream>
#include "LoadingList.h"
#include "rapidxml.hpp"

using std::cout;
using std::vector;
using std::ifstream;
using std::getline;
using rapidxml::xml_document;
using rapidxml::xml_node;



template <typename T>
T* LoadingList<T>:: preload(const string& name)
{
	for(vector<T>::iterator it = loadedList.begin(); it != loadedList.end(); it++)
		if(it->name == name)
			return &(*it);

	T newItem;

	newItem.name = name;

	loadedList.push_back(newItem);

	return &(*(loadedList.end()));
}

template <typename T>
const T& LoadingList<T>::get(const string& name)
{
	for(vector<T>::const_iterator it = loadedList.begin(); it != loadedList.end(); it++)
		if(it->name == name)
			return *it;

	try
	{
		load(name);			//'name' was not found on the list, so load it.
	}
	catch(...)
	{
		throw;
	}

	return loadedList[loadedList.size() - 1];
}

template <typename T>
vector<const T&> LoadingList<T>::getAllLoaded() const
{
	return loadedList;
}

template <typename T>
vector<const T&> LoadingList<T>::getAll()
{
	load();

	return getAllLoaded();
}


void CreoList::load(const string& name)
{
	try
	{
		ifstream ifs(dataFileName);			//loading data first

		if(!ifs)
		{
			ifs.close();

			throw "Creo data file \"" + dataFileName + "\" failed to open.";
		}
		
		bool foundItem = (name == "");

		xml_document<> xmlDoc;

		string oneline = "",
			fileText = "";

		while(getline(ifs, oneline))
			fileText += oneline;

		xmlDoc.parse<0>(&fileText[0]);

		int idNum = 1;

		for(xml_node<>* currentNode = xmlDoc.first_node()->first_node(); currentNode != NULL; currentNode = currentNode->next_sibling())
		{
			if((currentNode->first_attribute("id")->value() == name) || (name == ""))
			{
				foundItem = true;

				Creo* creoPtr = preload(name);

				creoPtr->id = idNum;

				creoPtr->element1 = currentNode->first_attribute("element")->value();

				if(currentNode->first_attribute("element2"))
					creoPtr->element2 = currentNode->first_attribute("element2")->value();
				else creoPtr->element2 = creoPtr->element1;

				if(currentNode->first_attribute("class"))
					creoPtr->creoClass = currentNode->first_attribute("class")->value();
				else creoPtr->creoClass = "NONE";

				creoPtr->rarity = currentNode->first_attribute("rarity")->value();

				if(creoPtr->rarity == "COMMON")
				{
					creoPtr->levelUpSpeed = "SLOW";
					creoPtr->catchRate = 250;
					creoPtr->exp = 20;
					creoPtr->runChance = 0;
				}
				else if(creoPtr->rarity == "UNCOMMON")
				{
					creoPtr->levelUpSpeed = "MEDIUM_SLOW";
					creoPtr->catchRate = 200;
					creoPtr->exp = 50;
					creoPtr->runChance = 0;
				}
				else if(creoPtr->rarity == "RARE")
				{
					creoPtr->levelUpSpeed = "STANDARD";
					creoPtr->catchRate = 135;
					creoPtr->exp = 90;
					creoPtr->runChance = 1;
				}
				else if(creoPtr->rarity == "ASCENDENT")
				{
					creoPtr->levelUpSpeed = "MEDIUM_FAST";
					creoPtr->catchRate = 50;
					creoPtr->exp = 150;
					creoPtr->runChance = 2;
				}
				else if(creoPtr->rarity == "PRIME")
				{
					creoPtr->levelUpSpeed = "FAST";
					creoPtr->catchRate = 1;
					creoPtr->exp = 250;
					creoPtr->runChance = 3;
				}

				creoPtr->vitality = atof(currentNode->first_attribute("vitalitybase")->value());
				creoPtr->attack = atoi(currentNode->first_attribute("physicalbase")->value());
				creoPtr->special = atoi(currentNode->first_attribute("elementalbase")->value());
				creoPtr->speed = atoi(currentNode->first_attribute("speedbase")->value());
				creoPtr->defense = atoi(currentNode->first_attribute("defensebase")->value());

				creoPtr->weight = atof(currentNode->first_attribute("weight")->value());
				creoPtr->size = atof(currentNode->first_attribute("size")->value());

				for(xml_node<>* currentMove = currentNode->first_node("move"); currentMove != NULL; currentMove = currentMove->next_sibling())
				{
					
				}

				if(name != "")
					break;
			}

			idNum++;
		}

		ifs.close();

		if(!foundItem)
			throw "End of Creo data file \"" + dataFileName + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Creo data file \"" + dataFileName + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}
	
	try
	{
		ifstream ifs(stringsFileName);

		if(!ifs)
		{
			ifs.close();

			throw "Creo strings file \"" + stringsFileName + "\" failed to open.";
		}

		bool foundItem = (name == "");

		xml_document<> xmlDoc;

		string oneline = "",
			fileText = "";

		while(getline(ifs, oneline))
			fileText += oneline;

		xmlDoc.parse<0>(&fileText[0]);

		for(xml_node<>* currentNode = xmlDoc.first_node()->first_node(); currentNode != NULL; currentNode = currentNode->next_sibling())
		{
			if((currentNode->first_attribute()->value() == name + "_des") || (name == ""))
			{
				foundItem = true;

				Creo* creoPtr = preload(name);

				creoPtr->description = currentNode->value();

				if(name != "")
					break;
			}
		}

		ifs.close();

		if(!foundItem)
			throw "End of Creo strings file \"" + stringsFileName + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Creo strings file \"" + stringsFileName + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}
}


void MoveList::load(const string& name)
{
	try
	{
		ifstream ifs(dataFileName);			//loading data first

		if(!ifs)
		{
			ifs.close();

			throw "Moves data file \"" + dataFileName + "\" failed to open.";
		}
		
		bool foundItem = (name == "");

		xml_document<> xmlDoc;

		string oneline = "",
			fileText = "";

		while(getline(ifs, oneline))
			fileText += oneline;

		xmlDoc.parse<0>(&fileText[0]);

		for(xml_node<>* currentNode = xmlDoc.first_node()->first_node(); currentNode != NULL; currentNode = currentNode->next_sibling())
		{
			if((currentNode->first_attribute("id")->value() == name) || (name == ""))
			{
				foundItem = true;

				Move* movePtr = preload(name);

				movePtr->type = currentNode->first_attribute("type")->value();
				movePtr->element = currentNode->first_attribute("element")->value();

				if(currentNode->first_attribute("class"))
					movePtr->moveClass = currentNode->first_attribute("class")->value();
				else movePtr->moveClass = "NONE";

				movePtr->contactType = currentNode->first_attribute("contacttype")->value();
				movePtr->skillType = currentNode->first_attribute("skilltype")->value();

				movePtr->accuracy = atof(currentNode->first_attribute("accuracy")->value());

				movePtr->damage = atoi(currentNode->first_attribute("basedamage")->value());
				movePtr->recharge = atoi(currentNode->first_attribute("recharge")->value());

				if(currentNode->first_attribute("effect"))		//load 'effects' vector
				{
					movePtr->effects[0] = ChanceEffect(currentNode->first_attribute("effect")->value(), atof(currentNode->first_attribute("effectchance")->value()));

					if(currentNode->last_attribute("effect") != currentNode->first_attribute("effect"))
						movePtr->effects[1] = ChanceEffect(currentNode->last_attribute("effect")->value(), atof(currentNode->last_attribute("effectchance")->value()));
				}

				if(currentNode->first_attribute("condition"))	//load 'conditions' vector
				{
					movePtr->conditions[0] = ChanceEffect(currentNode->first_attribute("condition")->value(), atof(currentNode->first_attribute("conditionchance")->value()));

					if(currentNode->last_attribute("condition") != currentNode->first_attribute("condition"))
						movePtr->conditions[1] = ChanceEffect(currentNode->last_attribute("condition")->value(), atof(currentNode->last_attribute("conditionchance")->value()));
				}

				if(currentNode->first_attribute("boon"))		//load 'boons' vector
				{
					movePtr->boons[0] = ChanceEffect(currentNode->first_attribute("boon")->value(), atof(currentNode->first_attribute("boonchance")->value()));

					if(currentNode->last_attribute("boon") != currentNode->first_attribute("boon"))
						movePtr->boons[1] = ChanceEffect(currentNode->last_attribute("boon")->value(), atof(currentNode->last_attribute("boonchance")->value()));
				}

				if(name != "")
					break;
			}
		}

		ifs.close();

		if(!foundItem)
			throw "End of Moves data file \"" + dataFileName + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Moves data file \"" + dataFileName + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}

	try
	{
		ifstream ifs(stringsFileName);

		if(!ifs)
		{
			ifs.close();

			throw "Moves strings file \"" + stringsFileName + "\" failed to open.";
		}

		bool foundItem = (name == "");

		xml_document<> xmlDoc;

		string oneline = "",
			fileText = "";

		while(getline(ifs, oneline))
			fileText += oneline;

		xmlDoc.parse<0>(&fileText[0]);

		for(xml_node<>* currentNode = xmlDoc.first_node()->first_node(); currentNode != NULL; currentNode = currentNode->next_sibling())
		{
			if((currentNode->first_attribute()->value() == name + "_des") || (name == ""))
			{
				foundItem = true;

				Move* movePtr = preload(name);

				movePtr->description = currentNode->value();

				if(name != "")
					break;
			}
		}

		ifs.close();

		if(!foundItem)
			throw "End of Moves strings file \"" + stringsFileName + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Moves strings file \"" + stringsFileName + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}
}


void TraitList::load(const string& name)
{
	try
	{
		ifstream ifs(stringsFileName);

		if(!ifs)
		{
			ifs.close();

			throw "Traits file \"" + stringsFileName + "\" failed to open.";
		}

		string oneline = "";
		
		while(oneline != "    <!--   Trait and ability Strings  -->")
			getline(ifs, oneline);

		getline(ifs, oneline);	//The header comment has another comment line below it.

		getline(ifs, oneline);	//doing this before the loop and at end of each iteration so a blank line doesn't get parsed

		bool foundItem = (name == "");

		xml_document<> xmlDoc;

		while(oneline != "")	//There is a blank line between traits and abilities.
		{
			xmlDoc.parse<0>(&oneline[0]);

			if((xmlDoc.first_attribute()->value() == name + "_des") || (name == ""))
			{
				foundItem = true;

				Trait* traitPtr = preload(name);

				traitPtr->description = xmlDoc.value();

				if(name != "")
					break;
			}

			getline(ifs, oneline);
		}

		ifs.close();

		if(!foundItem)
			throw "End of Traits file \"" + stringsFileName + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Traits file \"" + stringsFileName + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}
}


void AbilityList::load(const string& name)
{
	try
	{
		ifstream ifs(stringsFileName);

		if(!ifs)
		{
			ifs.close();

			throw "Abilities file \"" + stringsFileName + "\" failed to open.";
		}

		string oneline = "";
		
		while(oneline != "    <!--   Trait and ability Strings  -->")
			getline(ifs, oneline);

		while(oneline != "")
			getline(ifs, oneline);	//move down past the traits to the abilities section

		getline(ifs, oneline);		//doing this before the loop and at end of each iteration so a blank line doesn't get parsed

		bool foundItem = (name == "");

		xml_document<> xmlDoc;

		while(oneline != "")		//Go through the abilities up to the next black line (after the end).
		{
			xmlDoc.parse<0>(&oneline[0]);

			if((xmlDoc.first_attribute()->value() == name + "_des") || (name == ""))
			{
				foundItem = true;

				Ability* abilityPtr = preload(name);

				abilityPtr->description = xmlDoc.value();

				if(name != "")
					break;
			}

			getline(ifs, oneline);
		}

		ifs.close();

		if(!foundItem)
			throw "End of Abilities file \"" + stringsFileName + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Abilities file \"" + stringsFileName + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}
}