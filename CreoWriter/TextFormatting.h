// This file just contains functions that change text formatting.
// When a CreoLoader loads data, all strings are in all caps with underscores for spaces.
// For writing wiki pages, sometimes the strings have to be in "normal" format (first letter capitalized, spaces instead of underscores).
// Sometimes they have to be first letter capitalized but with underscores instead of spaces.

#ifndef TEXTFORMATTING_H
#define TEXTFORMATTING_H

#include <string>

using std::string;



string firstCaps(const string& oldString, const bool underscoresToSpaces = true);
	//make lowercase all letters not preceded by a space or underscore
	//optionally convert underscores to spaces (does this by default)

#endif