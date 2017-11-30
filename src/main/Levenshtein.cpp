#include <iostream>
#include <string>
#include <unistd.h>

#include "Computer.h"


//----------------------------------VARIABLES-----------------------------------
bool AlignOption = false;
//bool DistanceOption = false;

//--------------------------------PROCEDURES------------------------------------
void displayHelp ( );
void displayHelp ( )
{
	std::cout << "Usage : Levenshtein [-a]" << std::endl;
}
//-----------------------------------MAIN---------------------------------------
int main (int argc, char ** args)
{
	int i = 1;
	char option;
	while ( (option = getopt(argc, args, "ah")) != -1 )
	{
		switch ( option )
		{
			case 'a' :
				AlignOption = true;
				break;
			case 'h' :
			default :
				displayHelp();
				return 0;
		}

		i++;
	}


	std::string a,b;
	getline(std::cin,a);
	getline(std::cin,b);
	Levenshtein::Computer computer (a,b);

#ifdef DEBUG
	computer.PrintScore(std::cerr);
	computer.PrintBackTrack(std::cerr);
#endif

	std::cout << computer.Distance() << std::endl;

	if ( AlignOption )
	{
		computer.PrintAlignment(std::cout);
	}

	return 0;
}
