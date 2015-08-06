#include <string>
#include "TextFormatting.h"

using std::string;

string firstCaps(const string& oldString, const bool underscoresToSpaces)
{
	if(oldString.substr(0, 8) == "ARCANE_v")
		return "Arcane V" + oldString.substr(8,1);

	string newString = "";

	bool firstLetter = true;

	for(unsigned int i = 0; i < oldString.size(); i++)
	{
		if(oldString[i] == '_')
		{
			firstLetter = true;

			if(underscoresToSpaces)
				newString += ' ';
			else
				newString += '_';
		}
		else if(!firstLetter)
		{
			if(oldString[i] == 'A')
				newString += 'a';

			else if(oldString[i] == 'B')
				newString += 'b';

			else if(oldString[i] == 'C')
				newString += 'c';

			else if(oldString[i] == 'D')
				newString += 'd';

			else if(oldString[i] == 'E')
				newString += 'e';

			else if(oldString[i] == 'F')
				newString += 'f';

			else if(oldString[i] == 'G')
				newString += 'g';

			else if(oldString[i] == 'H')
				newString += 'h';

			else if(oldString[i] == 'I')
				newString += 'i';

			else if(oldString[i] == 'J')
				newString += 'j';

			else if(oldString[i] == 'K')
				newString += 'k';

			else if(oldString[i] == 'L')
				newString += 'l';

			else if(oldString[i] == 'M')
				newString += 'm';

			else if(oldString[i] == 'N')
				newString += 'n';

			else if(oldString[i] == 'O')
				newString += 'o';

			else if(oldString[i] == 'P')
				newString += 'p';

			else if(oldString[i] == 'Q')
				newString += 'q';

			else if(oldString[i] == 'R')
				newString += 'r';

			else if(oldString[i] == 'S')
				newString += 's';

			else if(oldString[i] == 'T')
				newString += 't';

			else if(oldString[i] == 'U')
				newString += 'u';

			else if(oldString[i] == 'V')
				newString += 'v';

			else if(oldString[i] == 'W')
				newString += 'w';

			else if(oldString[i] == 'X')
				newString += 'x';

			else if(oldString[i] == 'Y')
				newString += 'y';

			else if(oldString[i] == 'Z')
				newString += 'z';

			else
				newString += oldString[i];
		}
		else
		{
			newString += oldString[i];

			firstLetter = false;
		}
	}

	return newString;
}