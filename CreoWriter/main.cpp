#include <iostream>
#include "CreoLoader.h"

using std::cout;



int main(int argc, const char *argv[])
{
	CreoLoader creoLoader;

	vector<const Creo*> creoList = creoLoader.getAllCreo();

	for(vector<const Creo*>::const_iterator it = creoList.begin(); it != creoList.end(); it++)
		(*it)->writeWikiaPage();

	return 0;
}