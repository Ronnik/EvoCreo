#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include "Creo.h"
#include "TextFormatting.h"

using std::string;
using std::to_string;
using std::cout;
using std::vector;
using std::stack;
using std::ofstream;



Evolution::Evolution(const Creo* evolvedCreo, const int evolutionLevel)
{
	creo = evolvedCreo;
	type = 0;
	level = evolutionLevel;
	element = "";
}

Evolution::Evolution(const Creo* evolvedCreo, const string& evolutionElement)
{
	creo = evolvedCreo;
	type = 1;
	level = 0;
	element = evolutionElement;
}



Creo::Creo(const string& nameArg, const string& descriptionArg, const string& element1Arg, const string& element2Arg, const string& creoClassArg, const string& rarityArg, const string& levelUpSpeedArg, const int vitalityArg, const int attackArg, const int specialArg, const int speedArg, const int defenseArg, const int catchRateArg, const int expArg, const int runChanceArg, const float weightArg, const float sizeArg, const vector<LearnedSkill<Move>>& eliteMovesArg, const vector<LearnedSkill<Move>>& normalMovesArg, const vector<LearnedSkill<Move>>& healingMovesArg, const vector<LearnedSkill<Trait>>& traitsArg, const vector<LearnedSkill<Ability>>& abilitiesArg, const vector<const Move*>& tomeMovesArg, const vector<Evolution>& evolutionsArg, const Creo* previousStageArg)
{
	name = nameArg;
	description = descriptionArg;
	element1 = element1Arg;
	element2 = element2Arg;
	creoClass = creoClassArg;
	rarity = rarityArg;
	levelUpSpeed = levelUpSpeedArg;

	vitality = vitalityArg;
	attack = attackArg;
	special = specialArg;
	speed = speedArg;
	defense = defenseArg;
	catchRate = catchRateArg;
	exp = expArg;
	runChance = runChanceArg;

	weight = weightArg;
	size = sizeArg;

	eliteMoves = eliteMovesArg;
	normalMoves = normalMovesArg;
	healingMoves = healingMovesArg;

	traits = traitsArg;

	abilities =	abilitiesArg;

	tomeMoves = tomeMovesArg;

	evolutions = evolutionsArg;

	previousStage = previousStageArg;

	//The creo's Creopedia number isn't stored in the data or strings files (it's probably in the code),
	//so I hard-coded this array to look it up manually.
	id = 0;
	
	const int numberOfCreo = 133;

	const string creoOrder[numberOfCreo] = {"FYROEY", "FYRABY", "FYRU", "MONKOPOD", "KENTROPOD", "STEGOPOD", "SKALANKA", "SKALUNNE", "SKALORN", "DEOR", "ALCERRA", "CERVUCEAN", "RANGIFAIR", "RUSARTH", "DETRON", "CERVANTES", "CERMINOUS", "NULIFER", "ELACAT", "ELATRIKE", "TRUEGATO", "SQUIRIAN", "ARMIGHT", "SOLEAT", "SOLATE", "CLOUFI", "SINGLISH", "SHOALISH", "SCHOOLISH", "SEADRAKE", "LEAFDRA", "ONGADRA", "BLIXDRA", "ORKANDRA", "MUDRA", "LUFTDRA", "LUMDRA", "NULDRA", "REBAS", "VOLCADON", "REGODON", "GLACIADON", "WILLODON", "REBTRIX", "AERODON", "SOLDON", "NULDON", "BALLOO", "ROLO", "MOTCEE", "NAJA", "ARMAJA", "KODOCK", "AERAJA", "IGNODO", "CONLEON", "HYDRAJA", "SALDO", "OBSIUS", "FULGET", "FULGEDEUS", "CHESHATTER", "MADIREKAT", "BRUNK", "TERRANO", "SEACEAN", "VULKAN", "BLIX", "RADOW", "FERREDOW", "RAVIAN", "ILLUVIAN", "ARMONIA", "SHADIAIR", "SHADIGON", "LUMINEAM", "LUMIGON", "POLYCRYST", "SKARN", "IGNISAKHRA", "AQUASTEN", "NAVITERRA", "ACERTH", "MUSGORD", "CRYSTSOL", "AMORPHURE", "SEGLAR", "DYKAR", "VALNOT", "VALROOT", "VALTREE", "FUREN", "FURNIS", "FUROST", "BREAR", "VARGTRON", "LOBONK", "SHOG", "LUPINOUS", "VULPOID", "VULPESOL", "ARCUS", "NOCTERRA", "CONFAL", "NALTAIR", "JAMAD", "KAHRUS", "NABAT", "NOORI", "SWARTEAU", "NOOROUH", "GRIPONY", "EQUAVES", "TRIOPUS", "HEPTAPUS", "SCARASECT", "TERRASECT", "HEMISHADE", "HEMISHIELD", "POPONO", "PEPITA", "PEPON", "PEPTEIN", "HIELO", "EMPERUIN", "ARCANE_v1", "ARCANE_v2", "ARCANE_v3", "KRABEL", "HIPPOKRAB", "CHERRY_BOMB", "AERIALANX", "MIZAN"};

	for(int i = 0; i < numberOfCreo; i++)
		if(name == creoOrder[i])
		{
			id = i + 1;

			break;
		}
}

void Creo::writeWikiaPage(string filename) const
{
	ofstream ofs;

	if(filename == "")
		filename = to_string(id) + "_" + name + ".txt";

	cout << "\nWriting page for \"" + name + "\" as \"" + filename + "\"...";

	try
	{
		ofs.open(filename);
	}
	catch(...)
	{
		cout << "\nError: could not create output file.\n";
		throw;
	}

	//This is where the template is filled.
	//Most of it is hard-coded, which I know is bad practice, but why bother making a completely customizable template
	//for this small, almost single-use project?

	ofs << "{| cellpadding=\"8px\" align=\"center\" style=\"text-align:center;"
		<< "\n|[[File:Active_Users_Icon.png|thumb|center|37px]]"
		<< "\n|[[File:Main_Page_Icon.png|thumb|center|50px|link=]]"
		<< "\n|[[File:Tutorial_Icon.png|thumb|center|50px|link=Tutorial]]"
		<< "\n|[[File:Creopedia_Icon.png|thumb|center|50px|link=Creopedia]]"
		<< "\n|[[File:Walkthrough_Icon.png|thumb|center|50px|link=Walkthrough]]"
		<< "\n|[[File:Items_Icon.png|thumb|center|45px|link=Items]]"
		<< "\n|[[File:RAD's_Icon.png|thumb|center|50px|link=RADs]]"
		<< "\n|[[File:Locations_Icon.png|thumb|center|50px|link=Locations]]"
		<< "\n|[[File:Shop_icon.png|thumb|center|link=Shop]]"
		<< "\n|[[File:Updates_Icon.png|thumb|center|50px|link=Updates]]"
		<< "\n|-"
		<< "\n| style=\"text-align:center;\" |[[Special:ListUsers|Active Users]]"
		<< "\n| style=\"text-align:center;\" |[[Main Page]]"
		<< "\n| style=\"text-align:center;\" |[[Tutorial]]"
		<< "\n| style=\"text-align:center;\" |[[Creopedia]]"
		<< "\n| style=\"text-align:center;\" |[[Walkthrough]]"
		<< "\n| style=\"text-align:center;\" |[[Items]]"
		<< "\n| style=\"text-align:center;\" |[[RADs]]"
		<< "\n| style=\"text-align:center;\" |[[Locations]]"
		<< "\n| style=\"text-align:center;\" |[[Shop]]"
		<< "\n| style=\"text-align:center;\" |[[Updates]]"
		<< "\n|}"
		<< "\n"
		<< "\n"
		<< "\n[[File:Information_Title.png|center]]"
		<< "\n"
		<< "\n"
		<< "\n{| class=\"article-table\" align=\"center\""
		<< "\n!Name:"
		<< "\n|" << firstCaps(name)
		<< "\n|-"
		<< "\n!Creopedia:"
		<< "\n|#";
			if(id < 100)
				ofs << 0;
			if(id < 10)
				ofs << 0;
			ofs << id
		<< "\n|-"
		<< "\n!Normal Sprite:"
		<< "\n|[[File:-" << to_string(id) << "_" << firstCaps(name, false) << ".png|left]]"
		<< "\n|-"
		<< "\n!Genetically Modified Sprite:"
		<< "\n|[[File:-" << to_string(id) << "_" << firstCaps(name, false) << "2.png|left]]"
		<< "\n|-"
		<< "\n!Shiny Sprite:"
		<< "\n|[[File:-" << to_string(id) << "_" << firstCaps(name, false) << "3.png|left]]"
		<< "\n|-"
		<< "\n!Element 1:"
		<< "\n|" << firstCaps(element1)
		<< "\n|-"
		<< "\n!Element 2:"
		<< "\n|" << firstCaps(element2)
		<< "\n|-"
		<< "\n!Class:"
		<< "\n|" << firstCaps(creoClass)
		<< "\n|-"
		<< "\n!Rarity:"
		<< "\n|" << firstCaps(rarity)
		<< "\n|-"
		<< "\n!Evolution Stage:"
		<< "\n|";
			int stage = 1;
			for(const Creo* stageTrav = previousStage; stageTrav != NULL; stageTrav = stageTrav->previousStage)
				stage++;		//going all the way back through the chain of previous stages and incrementing 'stage' each time
			ofs << stage
		<< "\n|-"
		<< "\n!Catch Rate:"
		<< "\n|" << catchRate << "/250*"
		<< "\n|-"
		<< "\n!Run Chance:"
		<< "\n|"; 
			if(runChance == 0)
				ofs << "None";
			else if(runChance == 1)
				ofs << "Low";
			else if(runChance == 2)
				ofs << "Fair";
			else if(runChance == 3)
				ofs << "High";
	ofs << "\n|-"
		<< "\n!Weight:"
		<< "\n|" << weight << "kg"
		<< "\n|-"
		<< "\n!Size:"
		<< "\n|" << size << 'm'
		<< "\n|-"
		<< "\n!Description:"
		<< "\n|" << description
		<< "\n|}"
		<< "\n<p style=\"text-align:center;\">*Catch Rate represents how easy the Creo is to catch, 1 being the hardest.</p>"
		<< "\n"
		<< "\n<p style=\"text-align:center;\">[[File:Evolution_Title.png|center]]"
		<< "\n" << getFormattedEvolutionTree() << "</p>"
		<< "\n"
		<< "\n[[File:Moves_Title.png|center]]"
		<< "\n"
		<< "\n"
		<< "\n[[File:Elite_Title.png|thumb|center|118px]]"
		<< getFormattedMovesTable(eliteMoves)
		<< "\n"
		<< "\n[[File:Normal_Title.png|thumb|center|118px]]"
		<< getFormattedMovesTable(normalMoves)
		<< "\n"
		<< "\n[[File:Healing_Title.png|thumb|center|118px]]"
		<< getFormattedMovesTable(healingMoves)
		<< "\n"
		<< "\n[[File:Traits_Title.png|thumb|center|167px]]"
		<< "\n{| class=\"article-table\" align=\"center\""
		<< "\n!Name"
		<< "\n!Level"
		<< "\n!Description";
			for(vector<LearnedSkill<Trait>>::const_iterator it = traits.begin(); it!=traits.end(); it++)
			{
				ofs << "\n|-"
					<< "\n|" << firstCaps((*it).info->name)
					<< "\n| style=\"text-align:center;\" |" << (*it).levelLearned
					<< "\n|" << (*it).info->description;
			}
			ofs << "\n|}"
		<< "\n"
		<< "\n[[File:Abilities_Title.png|thumb|center|167px]]"
		<< "\n{| class=\"article-table\" align=\"center\""
		<< "\n!Name"
		<< "\n!Level"
		<< "\n!Description";
			for(vector<LearnedSkill<Ability>>::const_iterator it = abilities.begin(); it!=abilities.end(); it++)
			{
				ofs << "\n|-"
					<< "\n|" << firstCaps((*it).info->name)
					<< "\n| style=\"text-align:center;\" |" << (*it).levelLearned
					<< "\n|" << (*it).info->description;
			}
			ofs << "\n|}"
		<< "\n<p style=\"margin-top:1em;margin-bottom:1em;\">"
		<< "\n</p>"
		<< "\n"
		<< "\n<p style=\"margin-top:1em;margin-bottom:1em;\">"
		<< "\n</p>"
		<< "\n"
		<< "\n<p style=\"margin-top:1em;margin-bottom:1em;\">[[File:Tome_Teaching_Title.png|thumb|center|380px]]</p>"
		<< getFormattedTomeMovesTable()
		<< "\n"
		<< "\n[[File:Location_Title.png|center]]"
		<< "\n"
		<< "\n[[File:" << firstCaps(name, false) << "_Location.png|center|600px]]"
		<< "\n"
		<< "\n<p style=\"text-align: center;\">Other Locations:</p>";
	
	ofs.close();

	cout << "\nDone: " + filename;
}

string Creo::getFormattedEvolutionTree(stack<string> branches) const
{
	if(previousStage)
	{
		branches.push(name);

		return previousStage->getFormattedEvolutionTree(branches);
	}
	else
	{
		const Creo* currentCreo = this;

		vector<Evolution>::const_iterator evoTrav;

		stack<string> branchesTmp = branches;

		while(!branchesTmp.empty())
		{
			for(evoTrav = currentCreo->evolutions.begin();(*evoTrav).creo->name != branchesTmp.top(); evoTrav++);

			currentCreo = (*evoTrav).creo;

			branchesTmp.pop();
		}

		if(currentCreo->evolutions.size())
		{
			string tree = "";

			for(vector<Evolution>::const_iterator evoTrav = currentCreo->evolutions.begin(); evoTrav != currentCreo->evolutions.end(); evoTrav++)
				tree += (*evoTrav).creo->getFormattedEvolutionTree();
			
			return tree;
		}
		else
		{
			currentCreo = this;

			string tree = "\n<gallery hideaddbutton=\"true\" columns=\"" + to_string(2 * branches.size() + 1) + "\" position=\"center\" spacing=\"small\" widths=\"67\" mode=\"nolines\" bordercolor=\"transparent\" captionalign=\"center\" captionsize=\"large\" navigation=\"true\">";

			int branchesSize = branches.size();

			for(int i = 0; i < branchesSize + 1; i++)
			{
				tree += "\n-" + to_string(currentCreo->id) + "_" + firstCaps(currentCreo->name, false) + ".png|" + firstCaps(currentCreo->name) + "|link=" + firstCaps(currentCreo->name, false);

				if(i < branchesSize)
				{
					for(evoTrav = currentCreo->evolutions.begin(); (*evoTrav).creo->name != branches.top(); evoTrav++);

					currentCreo = (*evoTrav).creo;

					branches.pop();

					if((*evoTrav).type == 0)
					{
						tree += "\nlevel up arrow.png|Lvl." + to_string((*evoTrav).level);
					}
					else if((*evoTrav).type == 1)
					{
						tree += "\n" + firstCaps((*evoTrav).element, false) + " Element.png|" + firstCaps((*evoTrav).element);
					}
				}

			}

			tree += "\n</gallery>\n";

			return tree;
		}
	}
}

string Creo::getFormattedMovesTable(const vector<LearnedSkill<Move>>& movesVector) const
{
	string tblSource = "\n{| class=\"article-table\" align=\"center\"";
		tblSource += "\n!Name";
		tblSource += "\n!Icon";
		tblSource += "\n!Level";
		tblSource += "\n!Description";
		tblSource += "\n!Element";

	for(vector<LearnedSkill<Move>>::const_iterator it = movesVector.begin(); it!=movesVector.end(); it++)
	{
		tblSource += "\n|-";
		tblSource += "\n|[[" + firstCaps((*it).info->name) + "]]";
		tblSource += "\n| style=\"text-align:center;\" |[[File:" + firstCaps((*it).info->name, false) + ".png|center]]";
		tblSource += "\n| style=\"text-align:center;\" |" + to_string((*it).levelLearned);
		tblSource += "\n|" + (*it).info->description;
		tblSource += "\n|" + firstCaps((*it).info->element);
	}

		tblSource += "\n|}";

	return tblSource;
}

string Creo::getFormattedTomeMovesTable() const
{
	string basicTomeNames[] = {"Normality", "Fire", "Water", "Air", "Earth", "Nature", "Electricity", "Light", "Darkness"};
	string eliteTomeNames[] = {"The Ordinary", "Hellfire", "The Tsunami", "Gale", "The Mountain", "The Jungle", "The Storm", "Divinity", "The Void"};
	string elementNames[] = {"NORMAL", "FIRE", "WATER", "AIR", "EARTH", "NATURE", "ELECTRIC", "LIGHT", "DARK"};

	int element1Num = -1,
		element2Num = -1;

	for(int i = 0; i < 9; i++)
	{
		if(element1 == elementNames[i])
			element1Num = i;
		if(element2 == elementNames[i])
			element2Num = i;
	}

	string tblSource = "\n{| class=\"article-table\" align=\"center\"";
		tblSource += "\n!Tome Name";
		tblSource += "\n!Move Taught";
		tblSource += "\n!Icon";
		tblSource += "\n!Description";
		tblSource += "\n!Element";
		tblSource += "\n!Move Type";

	vector<const Move*>::const_iterator it = tomeMoves.begin();

	for(int i = 0; i < 9; i++, it++)
	{
		tblSource += "\n|-";
		tblSource += "\n|'''Tome of " + basicTomeNames[i] + "'''";
		tblSource += "\n|[[" + firstCaps((*it)->name) + "]]";
		tblSource += "\n|[[File:" + firstCaps((*it)->name, false) + ".png|center]]";
		tblSource += "\n|" + (*it)->description;
		tblSource += "\n|" + firstCaps((*it)->element);
		tblSource += "\n|" + firstCaps((*it)->skillType);
	}

		tblSource += "\n|-";
		tblSource += "\n|'''Tome of " + eliteTomeNames[element1Num] + "'''";
		tblSource += "\n|[[" + firstCaps((*it)->name) + "]]";
		tblSource += "\n|[[File:" + firstCaps((*it)->name, false) + ".png|center]]";
		tblSource += "\n|" + (*it)->description;
		tblSource += "\n|" + firstCaps((*it)->element);
		tblSource += "\n|" + firstCaps((*it)->skillType) + " Move";

		if(element1Num != element2Num)
		{
			++it;

			tblSource += "\n|-";
			tblSource += "\n|'''Tome of " + eliteTomeNames[element2Num] + "'''";
			tblSource += "\n|[[" + firstCaps((*it)->name) + "]]";
			tblSource += "\n|[[File:" + firstCaps((*it)->name, false) + ".png|center]]";
			tblSource += "\n|" + (*it)->description;
			tblSource += "\n|" + firstCaps((*it)->element);
			tblSource += "\n|" + firstCaps((*it)->skillType);
		}

		tblSource += "\n|}";

	return tblSource;
}