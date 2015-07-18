#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CreoLoader.h"
#include "rapidxml.hpp"

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::ifstream;
using std::getline;
using rapidxml::xml_document;
using rapidxml::xml_node;
using rapidxml::xml_attribute;



template <typename T>
T* CreoLoader::preload(vector<T*>& list, const string& name)
{
	for(vector<T*>::iterator it = list.begin(); it != list.end(); it++)
		if((*it)->name == name)
			return *it;

	T* newItemPtr = new T(name);

	list.push_back(newItemPtr);

	return list[list.size() - 1];
}

template <typename T>
T* CreoLoader::get(const string& name, vector<T*>& list)
{
	for(vector<T*>::iterator it = list.begin(); it != list.end(); it++)
		if((*it)->name == name)
			return *it;

	return NULL;
}

CreoLoader::CreoLoader(const string& creoDataFilenameArg, const string& creoStringsFilenameArg, const string& moveDataFilenameArg, const string& moveStringsFilenameArg, const string& sceneStringsFilenameArg)
{
	creoDataFilename = creoDataFilenameArg;
	creoStringsFilename = creoStringsFilenameArg;
	moveDataFilename = moveDataFilenameArg;
	moveStringsFilename = moveStringsFilenameArg;
	sceneStringsFilename = sceneStringsFilenameArg;
}

CreoLoader::~CreoLoader()
{
	for(vector<Creo*>::iterator it = creoList.begin(); it != creoList.end(); it++)
		delete *it;

	for(vector<Move*>::iterator it = moveList.begin(); it != moveList.end(); it++)
		delete *it;

	for(vector<Trait*>::iterator it = traitList.begin(); it != traitList.end(); it++)
		delete *it;

	for(vector<Ability*>::iterator it = abilityList.begin(); it != abilityList.end(); it++)
		delete *it;

	for(vector<Effect*>::iterator it = effectList.begin(); it != effectList.end(); it++)
		delete *it;

	for(vector<Condition*>::iterator it = conditionList.begin(); it != conditionList.end(); it++)
		delete *it;

	for(vector<Boon*>::iterator it = boonList.begin(); it != boonList.end(); it++)
		delete *it;
}

void CreoLoader::loadCreo(const string& name)
{
	if(name != "")
		cout << "\nLoading \"" + name + "\"...";

	try
	{
		ifstream ifs(creoDataFilename);			//loading data first

		if(!ifs)
		{
			ifs.close();

			throw "Creo data file \"" + creoDataFilename + "\" failed to open.";
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

				Creo* creoPtr = preload(creoList, currentNode->first_attribute("id")->value());

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

				creoPtr->eliteMoves = vector<LearnedSkill<Move>>();
				creoPtr->normalMoves = vector<LearnedSkill<Move>>();
				creoPtr->healingMoves = vector<LearnedSkill<Move>>();
				for(xml_node<>* currentMove = currentNode->first_node("move"); currentMove != NULL; currentMove = currentMove->next_sibling("move"))
				{
					LearnedSkill<Move> learnedMove(getMove(currentMove->first_attribute("id")->value()), atoi(currentMove->first_attribute("level")->value()));

					if(learnedMove.info->skillType == "ELITE")
						creoPtr->eliteMoves.push_back(learnedMove);
					else if(learnedMove.info->skillType == "NORMAL")
						creoPtr->normalMoves.push_back(learnedMove);
					else if(learnedMove.info->skillType == "HEALING")
						creoPtr->healingMoves.push_back(learnedMove);
				}

				const Move* tomeMoves[11];

				for(xml_node<>* currentTome = currentNode->first_node("movecompatible"); currentTome != NULL; currentTome = currentTome->next_sibling("movecompatible"))
				{
					const Move* move = getMove(currentTome->first_attribute("move")->value());

					string tomeName = currentTome->first_attribute("id")->value();

					if(tomeName == "TOME_OF_NORMALITY")
						tomeMoves[0] = move;
					else if(tomeName == "TOME_OF_FIRE")
						tomeMoves[1] = move;
					else if(tomeName == "TOME_OF_WATER")
						tomeMoves[2] = move;
					else if(tomeName == "TOME_OF_AIR")
						tomeMoves[3] = move;
					else if(tomeName == "TOME_OF_EARTH")
						tomeMoves[4] = move;
					else if(tomeName == "TOME_OF_NATURE")
						tomeMoves[5] = move;
					else if(tomeName == "TOME_OF_ELECTRICITY")
						tomeMoves[6] = move;
					else if(tomeName == "TOME_OF_LIGHT")
						tomeMoves[7] = move;
					else if(tomeName == "TOME_OF_DARKNESS")
						tomeMoves[8] = move;
					else if(move->element == creoPtr->element1)
						tomeMoves[9] = move;
					else if(move->element == creoPtr->element2)		//"else if", so it can't happen if element1 == element2
						tomeMoves[10] = move;
				}

				creoPtr->tomeMoves = vector<const Move*>();
				for(int i = 0; i < 10; i++)
					creoPtr->tomeMoves.push_back(tomeMoves[i]);

				if(creoPtr->element1 != creoPtr->element2)
					creoPtr->tomeMoves.push_back(tomeMoves[10]);

				creoPtr->traits = vector<LearnedSkill<Trait>>();
				for(xml_node<>* currentTrait = currentNode->first_node("trait"); currentTrait != NULL; currentTrait = currentTrait->next_sibling("trait"))
					creoPtr->traits.push_back(LearnedSkill<Trait>(getTrait(currentTrait->first_attribute("id")->value()), atoi(currentTrait->first_attribute("level")->value())));

				creoPtr->abilities = vector<LearnedSkill<Ability>>();
				for(xml_node<>* currentAbility = currentNode->first_node("ability"); currentAbility != NULL; currentAbility = currentAbility->next_sibling("ability"))
					creoPtr->abilities.push_back(LearnedSkill<Ability>(getAbility(currentAbility->first_attribute("id")->value()), atoi(currentAbility->first_attribute("level")->value())));

				creoPtr->evolutions = vector<Evolution>();
				for(xml_node<>* currentEvolution = currentNode->first_node("evolution"); currentEvolution != NULL; currentEvolution = currentEvolution->next_sibling("evolution"))
				{
					creoPtr->evolutions.push_back(Evolution(getCreo(currentEvolution->first_attribute("id")->value()), atoi(currentEvolution->first_attribute("level")->value())));

					get(currentEvolution->first_attribute("id")->value(), creoList)->previousStage = creoPtr;
				}

				for(xml_node<>* currentEvolution = currentNode->first_node("evolutionelement"); currentEvolution != NULL; currentEvolution = currentEvolution->next_sibling("evolutionelement"))
				{
					creoPtr->evolutions.push_back(Evolution(getCreo(currentEvolution->first_attribute("id")->value()), currentEvolution->first_attribute("element")->value()));

					get(currentEvolution->first_attribute("id")->value(), creoList)->previousStage = creoPtr;
				}

				if(name != "")
					break;
			}

			idNum++;
		}

		ifs.close();

		if(!foundItem)
			cout << "\nError: End of Creo data file \"" + creoDataFilename + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Creo data file \"" + creoDataFilename + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}
	
	try
	{
		ifstream ifs(creoStringsFilename);

		if(!ifs)
		{
			ifs.close();

			throw "Creo strings file \"" + creoStringsFilename + "\" failed to open.";
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

				Creo* creoPtr = preload(creoList, string(currentNode->first_attribute()->value()).substr(0, string(currentNode->first_attribute()->value()).length() - 4));

				creoPtr->description = currentNode->value();

				if(name != "")
					break;
			}
		}

		ifs.close();

		if(!foundItem)
			cout << "\nError: End of Creo strings file \"" + creoStringsFilename + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Creo strings file \"" + creoStringsFilename + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}

	cout << "\nDone: " + name;
}

void CreoLoader::loadMove(const string& name)
{
	try
	{
		ifstream ifs(moveDataFilename);			//loading data first

		if(!ifs)
		{
			ifs.close();

			throw "Moves data file \"" + moveDataFilename + "\" failed to open.";
		}
		
		bool foundItem = (name == "");

		xml_document<> xmlDoc;

		string oneline = "",
			fileText = "";

		while(getline(ifs, oneline))
			fileText += oneline;

		xmlDoc.parse<0>(&fileText[0]);

		for(xml_node<>* currentNode = xmlDoc.first_node()->first_node(); currentNode != NULL; currentNode = currentNode->next_sibling("moveunit"))
		{
			if((currentNode->first_attribute("id")->value() == name) || (name == ""))
			{
				foundItem = true;

				Move* movePtr = preload(moveList, currentNode->first_attribute("id")->value());

				movePtr->type = currentNode->first_attribute("type")->value();
				movePtr->element = currentNode->first_attribute("element")->value();

				if(currentNode->first_attribute("class"))
					movePtr->moveClass = currentNode->first_attribute("class")->value();
				else movePtr->moveClass = "NONE";

				movePtr->contactType = currentNode->first_attribute("contacttype")->value();
				if(currentNode->first_attribute("skilltype"))
					movePtr->skillType = currentNode->first_attribute("skilltype")->value();

				if(currentNode->first_attribute("accuracy"))
					movePtr->accuracy = atof(currentNode->first_attribute("accuracy")->value());

				movePtr->damage = atoi(currentNode->first_attribute("basedamage")->value());
				movePtr->recharge = atoi(currentNode->first_attribute("recharge")->value());

				if(currentNode->first_attribute("effect"))		//load 'effects' vector
				{
					movePtr->effects.push_back(ChanceEffect<Effect>(getEffect(currentNode->first_attribute("effect")->value()), atof(currentNode->first_attribute("effectchance")->value())));

					if(currentNode->last_attribute("effect") != currentNode->first_attribute("effect"))
						movePtr->effects.push_back(ChanceEffect<Effect>(getEffect(currentNode->first_attribute("effect")->value()), atof(currentNode->last_attribute("effectchance")->value())));
				}

				if(currentNode->first_attribute("condition"))	//load 'conditions' vector
				{
					movePtr->conditions.push_back(ChanceEffect<Condition>(getCondition(currentNode->first_attribute("condition")->value()), atof(currentNode->first_attribute("conditionchance")->value())));

					if(currentNode->last_attribute("condition") != currentNode->first_attribute("condition"))
						movePtr->conditions.push_back(ChanceEffect<Condition>(getCondition(currentNode->first_attribute("condition")->value()), atof(currentNode->last_attribute("conditionchance")->value())));
				}

				if(currentNode->first_attribute("boon"))		//load 'boons' vector
				{
					movePtr->boons.push_back(ChanceEffect<Boon>(getBoon(currentNode->first_attribute("boon")->value()), atof(currentNode->first_attribute("boonchance")->value())));

					if(currentNode->last_attribute("boon") != currentNode->first_attribute("boon"))
						movePtr->boons.push_back(ChanceEffect<Boon>(getBoon(currentNode->last_attribute("boon")->value()), atof(currentNode->last_attribute("boonchance")->value())));
				}

				if(name != "")
					break;
			}
		}

		ifs.close();

		if(!foundItem)
			cout << "\nError: End of Moves data file \"" + moveDataFilename + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Moves data file \"" + moveDataFilename + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}

	try
	{
		ifstream ifs(moveStringsFilename);

		if(!ifs)
		{
			ifs.close();

			throw "Moves strings file \"" + moveStringsFilename + "\" failed to open.";
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

				Move* movePtr = preload(moveList, string(currentNode->first_attribute()->value()).substr(0, string(currentNode->first_attribute()->value()).length() - 4));

				movePtr->description = currentNode->value();

				if(name != "")
					break;
			}
		}

		ifs.close();

		if(!foundItem)
			cout << "\nError: End of Moves strings file \"" + moveStringsFilename + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Moves strings file \"" + moveStringsFilename + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}
}

void CreoLoader::loadTrait(const string& name)
{
	try
	{
		ifstream ifs(sceneStringsFilename);

		if(!ifs)
		{
			ifs.close();

			throw "Traits file \"" + sceneStringsFilename + "\" failed to open.";
		}

		string oneline = "";
		
		while(oneline != "    <!--   Trait and ability Strings  -->")
			getline(ifs, oneline);

		getline(ifs, oneline);	//The header comment has another comment line below it.

		getline(ifs, oneline);	//doing this before the loop and at end of each iteration so a blank line doesn't get parsed

		bool foundItem = (name == "");

		xml_document<> xmlDoc;

		while(oneline != "	")	//There is a blank line between traits and abilities.
		{
			xmlDoc.parse<0>(&oneline[0]);

			if((xmlDoc.first_node()->first_attribute()->value() == name + "_des") || (name == ""))
			{
				foundItem = true;

				Trait* traitPtr = preload(traitList, string(xmlDoc.first_node()->first_attribute()->value()).substr(0, string(xmlDoc.first_node()->first_attribute()->value()).length() - 4));

				traitPtr->description = xmlDoc.first_node()->value();

				if(name != "")
					break;
			}

			getline(ifs, oneline);
		}

		ifs.close();

		if(!foundItem)
			cout << "\nError: End of Traits file \"" + sceneStringsFilename + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Traits file \"" + sceneStringsFilename + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}
}

void CreoLoader::loadAbility(const string& name)
{
	try
	{
		ifstream ifs(sceneStringsFilename);

		if(!ifs)
		{
			ifs.close();

			throw "Abilities file \"" + sceneStringsFilename + "\" failed to open.";
		}

		string oneline = "";
		
		while(oneline != "    <!--   Trait and ability Strings  -->")
			getline(ifs, oneline);

		while(oneline != "	")
			getline(ifs, oneline);	//move down past the traits to the abilities section

		getline(ifs, oneline);		//doing this before the loop and at end of each iteration so a blank line doesn't get parsed

		bool foundItem = (name == "");

		xml_document<> xmlDoc;

		while(oneline != "")		//go through the abilities up to the next blank line (after the end)
		{
			xmlDoc.parse<0>(&oneline[0]);

			if((xmlDoc.first_node()->first_attribute()->value() == name + "_des") || (name == ""))
			{
				foundItem = true;

				Ability* abilityPtr = preload(abilityList, string(xmlDoc.first_node()->first_attribute()->value()).substr(0, string(xmlDoc.first_node()->first_attribute()->value()).length() - 4));

				abilityPtr->description = xmlDoc.first_node()->value();

				if(name != "")
					break;
			}

			getline(ifs, oneline);
		}

		ifs.close();

		if(!foundItem)
			cout << "\nError: End of Abilities file \"" + sceneStringsFilename + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Abilities file \"" + sceneStringsFilename + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}
}

void CreoLoader::loadEffect(const string& name)
{
	preload(effectList, name);		//nothing to load for effects but their names (no descriptions yet)
}

void CreoLoader::loadCondition(const string& name)
{
	try
	{
		ifstream ifs(sceneStringsFilename);

		if(!ifs)
		{
			ifs.close();

			throw "Conditions file \"" + sceneStringsFilename + "\" failed to open.";
		}

		string oneline = "";
		
		while(oneline != "    <!--         Cond/Boon Strings    -->")
			getline(ifs, oneline);

		while(oneline != "    ")
			getline(ifs, oneline);	//move down past the boons to the conditions section

		getline(ifs, oneline);		//doing this before the loop and at end of each iteration so a blank line doesn't get parsed

		bool foundItem = (name == "");

		xml_document<> xmlDoc;

		while(oneline != "    ")		//go through the conditions up to the next blank line (after the end)
		{
			xmlDoc.parse<0>(&oneline[0]);

			if((xmlDoc.first_node()->first_attribute()->value() == name) || (name == ""))
			{
				foundItem = true;

				Condition* conditionPtr = preload(conditionList, string(xmlDoc.first_node()->first_attribute()->value()));

				conditionPtr->description = xmlDoc.first_node()->value();

				if(name != "")
					break;
			}

			getline(ifs, oneline);
		}

		ifs.close();

		if(!foundItem)
			cout << "\nError: End of Conditions file \"" + sceneStringsFilename + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Conditions file \"" + sceneStringsFilename + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}
}

void CreoLoader::loadBoon(const string& name)
{
	try
	{
		ifstream ifs(sceneStringsFilename);

		if(!ifs)
		{
			ifs.close();

			throw "Boons file \"" + sceneStringsFilename + "\" failed to open.";
		}

		string oneline = "";
		
		while(oneline != "    <!--         Cond/Boon Strings    -->")
			getline(ifs, oneline);

		getline(ifs, oneline);	//The header comment has another comment line below it.

		getline(ifs, oneline);	//doing this before the loop and at end of each iteration so a blank line doesn't get parsed

		bool foundItem = (name == "");

		xml_document<> xmlDoc;

		while(oneline != "    ")	//There is a blank line between boons and conditions.
		{
			xmlDoc.parse<0>(&oneline[0]);

			if((xmlDoc.first_node()->first_attribute()->value() == name) || (name == ""))
			{
				foundItem = true;

				Boon* boonPtr = preload(boonList, string(xmlDoc.first_node()->first_attribute()->value()));

				boonPtr->description = xmlDoc.first_node()->value();

				if(name != "")
					break;
			}

			getline(ifs, oneline);
		}

		ifs.close();

		if(!foundItem)
			cout << "\nError: End of Boons file \"" + sceneStringsFilename + "\" reached. \"" + name + "\" was not found.";
	}
	catch(string loadErr)
	{
		cout << "\n" + loadErr + "\n";

		throw;
	}
	catch(...)
	{
		cout << "\nError encountered while reading Boons file \"" + sceneStringsFilename + "\": File may be incomplete or improperly formatted.\n";

		throw;
	}
}

void CreoLoader::loadAll()
{
	loadCreo();
	loadMove();
	loadTrait();
	loadAbility();
	//no loadEffect() right now because effects are not stored on file
	loadCondition();
	loadBoon();
}

const Creo* CreoLoader::getCreo(const string& name)
{
	Creo* creoPtr = get(name, creoList);

	if(creoPtr)
		return creoPtr;

	try
	{
		loadCreo(name);			//'name' was not found on the list, so load it.
	}
	catch(...)
	{
		cout << "\nError in CreoLoader::getCreo: could not load Creo \"" + name + "\".\n";

		throw;
	}

	return get(name, creoList);
}

const Move* CreoLoader::getMove(const string& name)
{
	Move* movePtr = get(name, moveList);

	if(movePtr)
		return movePtr;

	try
	{
		loadMove(name);			//'name' was not found on the list, so load it.
	}
	catch(...)
	{
		cout << "\nError in CreoLoader::getMove: could not load Move \"" + name + "\".\n";

		throw;
	}

	return get(name, moveList);
}

const Trait* CreoLoader::getTrait(const string& name)
{
	Trait* traitPtr = get(name, traitList);

	if(traitPtr)
		return traitPtr;

	try
	{
		loadTrait(name);		//'name' was not found on the list, so load it.
	}
	catch(...)
	{
		cout << "\nError in CreoLoader::getTrait: could not load Trait \"" + name + "\".\n";

		throw;
	}

	return get(name, traitList);
}

const Ability* CreoLoader::getAbility(const string& name)
{
	Ability* abilityPtr = get(name, abilityList);

	if(abilityPtr)
		return abilityPtr;

	try
	{
		loadAbility(name);		//'name' was not found on the list, so load it.
	}
	catch(...)
	{
		cout << "\nError in CreoLoader::getAbility: could not load Ability \"" + name + "\".\n";

		throw;
	}

	return get(name, abilityList);
}

const Effect* CreoLoader::getEffect(const string& name)
{
	Effect* effectPtr = get(name, effectList);

	if(effectPtr)
		return effectPtr;

	try
	{
		loadEffect(name);		//'name' was not found on the list, so load it.
	}
	catch(...)
	{
		cout << "\nError in CreoLoader::getEffect: could not load Effect \"" + name + "\".\n";

		throw;
	}

	return get(name, effectList);
}

const Condition* CreoLoader::getCondition(const string& name)
{
	Condition* conditionPtr = get(name, conditionList);

	if(conditionPtr)
		return conditionPtr;

	try
	{
		loadCondition(name);	//'name' was not found on the list, so load it.
	}
	catch(...)
	{
		cout << "\nError in CreoLoader::getCondition: could not load Condition \"" + name + "\".\n";

		throw;
	}

	return get(name, conditionList);
}

const Boon* CreoLoader::getBoon(const string& name)
{
	Boon* boonPtr = get(name, boonList);

	if(boonPtr)
		return boonPtr;

	try
	{
		loadBoon(name);			//'name' was not found on the list, so load it.
	}
	catch(...)
	{
		cout << "\nError in CreoLoader::getBoon: could not load Boon \"" + name + "\".\n";

		throw;
	}

	return get(name, boonList);
}

vector<const Creo*> CreoLoader::getAllCreo(bool loadAll)
{
	if(loadAll)
		loadCreo();

	vector<const Creo*> constantVector;

	for(vector<Creo*>::iterator it = creoList.begin(); it != creoList.end(); it++)
		constantVector.push_back(*it);

	return constantVector;
}

vector<const Move*> CreoLoader::getAllMoves(bool loadAll)
{
	if(loadAll)
		loadMove();

	vector<const Move*> constantVector;

	for(vector<Move*>::iterator it = moveList.begin(); it != moveList.end(); it++)
		constantVector.push_back(*it);

	return constantVector;
}

vector<const Trait*> CreoLoader::getAllTraits(bool loadAll)
{
	if(loadAll)
		loadTrait();

	vector<const Trait*> constantVector;

	for(vector<Trait*>::iterator it = traitList.begin(); it != traitList.end(); it++)
		constantVector.push_back(*it);

	return constantVector;
}

vector<const Ability*> CreoLoader::getAllAbilities(bool loadAll)
{
	if(loadAll)
		loadAbility();

	vector<const Ability*> constantVector;

	for(vector<Ability*>::iterator it = abilityList.begin(); it != abilityList.end(); it++)
		constantVector.push_back(*it);

	return constantVector;
}

vector<const Effect*> CreoLoader::getAllEffects()
{
	vector<const Effect*> constantVector;

	for(vector<Effect*>::iterator it = effectList.begin(); it != effectList.end(); it++)
		constantVector.push_back(*it);

	return constantVector;
}

vector<const Condition*> CreoLoader::getAllConditions(bool loadAll)
{
	if(loadAll)
		loadCondition();

	vector<const Condition*> constantVector;

	for(vector<Condition*>::iterator it = conditionList.begin(); it != conditionList.end(); it++)
		constantVector.push_back(*it);

	return constantVector;
}

vector<const Boon*> CreoLoader::getAllBoons(bool loadAll)
{
	if(loadAll)
		loadBoon();

	vector<const Boon*> constantVector;

	for(vector<Boon*>::iterator it = boonList.begin(); it != boonList.end(); it++)
		constantVector.push_back(*it);

	return constantVector;
}