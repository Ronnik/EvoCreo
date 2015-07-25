#include <iostream>
#include "CreoLoader.h"

using std::cout;



int main(int argc, const char *argv[])
{
	const bool writeCreoPages = false;
	const bool writeStatsComparison = false;
	const bool writeMovePages = false;

	CreoLoader creoLoader;

	if(writeCreoPages)
	{
		vector<const Creo*> creoList = creoLoader.getAllCreo();

		for(vector<const Creo*>::const_iterator it = creoList.begin(); it != creoList.end(); it++)
			(*it)->writeWikiaPage();
	}

	if(writeStatsComparison)
	{
		creoLoader.loadCreo();

		creoLoader.writeCreoStatsComparison();
	}

	if(writeMovePages)
	{
		vector<const Move*> moveList = creoLoader.getAllMoves();

		for(vector<const Move*>::const_iterator it = moveList.begin(); it != moveList.end(); it++)
			(*it)->writeWikiaPage();
	}
	
	return 0;
}