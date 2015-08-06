#include <iostream>
#include <fstream>
#include "Creo.h"
#include "Move.h"
#include "TextFormatting.h"

using std::cout;
using std::ofstream;
using std::to_string;



Move::Move(const string& nameArg, const string& descriptionArg, const string& typeArg, const string& elementArg, const string& moveClassArg, const string& contactTypeArg, const string& skillTypeArg, const float accuracyArg, const int powerArg, const int rechargeArg, const vector<ChanceEffect<Effect>> effectsArg, const vector<ChanceEffect<Condition>> conditionsArg, const vector<ChanceEffect<Boon>> boonsArg, vector<LearnedSkill<Creo>> creoLearnArg)
{
	name = nameArg;
	description = descriptionArg;
	type = typeArg;
	element = elementArg;
	moveClass = moveClassArg;
	contactType = contactTypeArg;
	skillType = skillTypeArg;

	accuracy = accuracyArg;

	power = powerArg;
	recharge = rechargeArg;

	effects = effectsArg;
	conditions = conditionsArg;
	boons = boonsArg;

	creoLearn = creoLearnArg;
}

void Move::writeWikiaPage(string filename) const
{
	ofstream ofs;

	if(filename == "")
		filename = "MOVE_" + name + ".txt";

	cout << "\nWriting page for Move \"" + name + "\" as \"" + filename + "\"...";

	try
	{
		ofs.open(filename);
	}
	catch(...)
	{
		cout << "\nError: could not create file.\n";
		throw;
	}

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
		<< "\n!Icon:"
		<< "\n|[[File:" << firstCaps(name) << ".png|left]]"
		<< "\n|-"
		<< "\n!Element:"
		<< "\n|" << firstCaps(element)
		<< "\n|-"
		<< "\n!Move Type:"
		<< "\n|" << firstCaps(type)
		<< "\n|-"
		<< "\n!Skill Type:"
		<< "\n|" << firstCaps(skillType) << " Move"
		<< "\n|-"
		<< "\n!Accuracy:"
		<< "\n|" << accuracy * 100.0 << "%"
		<< "\n|-"
		<< "\n!Power:"
		<< "\n|" << power
		<< "\n|-"
		<< "\n!Recharge:"
		<< "\n|" << recharge << " Turn";
			if(recharge != 1)
				ofs << 's';
	ofs << "\n|}"
		<< "\n"
		<< "\n"
		<< "\n<p style=\"text-align:center;\">" << description << "</p>"
		<< "\n==Effects=="
		<< "\n{| class=\"article-table\" align=\"center\""
		<< "\n!Name"
		<< "\n!Type"
		<< "\n!Chance"
		<< "\n!Description";
			for(vector<ChanceEffect<Boon>>::const_iterator it = boons.begin(); it != boons.end(); it++)
			{
				ofs << "\n|-"
					<< "\n|" + firstCaps((*it).info->name)
					<< "\n|Boon"
					<< "\n|" << (*it).chance * 100.0 << '%'
					<< "\n|" + (*it).info->description;
			}
			for(vector<ChanceEffect<Condition>>::const_iterator it = conditions.begin(); it != conditions.end(); it++)
			{
				ofs << "\n|-"
					<< "\n|" + firstCaps((*it).info->name)
					<< "\n|Condition"
					<< "\n|" << (*it).chance * 100.0 << '%'
					<< "\n|" + (*it).info->description;
			}
			for(vector<ChanceEffect<Effect>>::const_iterator it = effects.begin(); it != effects.end(); it++)
			{
				ofs << "\n|-"
					<< "\n|" + firstCaps((*it).info->name)
					<< "\n|Miscellaneous"
					<< "\n|" << (*it).chance * 100.0 << '%'
					<< "\n|" + (*it).info->description;
			}
	ofs << "\n|}"
		<< "\n"
		<< "\n==Learned by Level Up=="
		<< "\n{| class=\"article-table\" align=\"center\""
		<< "\n! style=\"text-align:center;\"|Number"
		<< "\n! style=\"text-align:center;\"|Image"
		<< "\n! style=\"text-align:center;\"|Name"
		<< "\n! style=\"text-align:center;\"|Level";
			for(vector<LearnedSkill<Creo>>::const_iterator it = creoLearn.begin(); it != creoLearn.end(); it++)
			{
				if((*it).levelLearned != 0)
				{
					ofs << "\n|-"
						<< "\n| style=\"text-align:center;\"|#";
							if((*it).info->id < 100)
							{
								ofs << 0;

								if((*it).info->id < 10)
									ofs << 0;
							}
					ofs << (*it).info->id
						<< "\n| style=\"text-align:center;\"|[[File:-" << (*it).info->id << "_" + firstCaps((*it).info->name) + ".png|center]]"
						<< "\n| style=\"text-align:center;\"|[[" + firstCaps((*it).info->name) + "]]"
						<< "\n| style=\"text-align:center;\"|" << (*it).levelLearned;
				}
			}
	ofs << "\n|}"
		<< "\n"
		<< "\n==Learned by Tome=="
		<< "\n{| class=\"article-table\" align=\"center\""
		<< "\n! style=\"text-align:center;\"|Number"
		<< "\n! style=\"text-align:center;\"|Image"
		<< "\n! style=\"text-align:center;\"|Name"
		<< "\n! style=\"text-align:center;\"|Tome";
			for(vector<LearnedSkill<Creo>>::const_iterator it = creoLearn.begin(); it != creoLearn.end(); it++)
			{
				if((*it).tomeName != "")
				{
					ofs << "\n|-"
						<< "\n| style=\"text-align:center;\"|#";
							if((*it).info->id < 100)
							{
								ofs << 0;

								if((*it).info->id < 10)
									ofs << 0;
							}
					ofs << (*it).info->id
						<< "\n| style=\"text-align:center;\"|[[File:-" << (*it).info->id << "_" + firstCaps((*it).info->name) + ".png|center]]"
						<< "\n| style=\"text-align:center;\"|[[" + firstCaps((*it).info->name) + "]]"
						<< "\n| style=\"text-align:center;\"|Tome of ";
							if((*it).tomeName.substr(8, 4) == "THE_")
								ofs << "the " + firstCaps((*it).tomeName.substr(12, (*it).tomeName.length() - 12));
							else
								ofs << firstCaps((*it).tomeName.substr(8, (*it).tomeName.length() - 8));
				}
			}
	ofs << "\n|}";
	
	ofs.close();

	cout << "\nDone: " + filename;
}