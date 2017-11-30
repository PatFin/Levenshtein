#include <iostream>
#include <string>
#include <stack>

#include "Computer.h"


//----------------------------------VARIABLES-----------------------------------


//----------------------------PROCEDURE DECLARATIONS----------------------------


//-----------------------------------MAIN---------------------------------------
int main (void)
{
	Levenshtein::Computer computer;
	std::string a,b;
	getline(std::cin,a);
	getline(std::cin,b);

	computer.init (a,b);
	computer.computeScoreAndBacktrack();

#ifdef DEBUG
	computer.displayScore();
	computer.displayBackTrack();
#endif

	std::cout << computer.GetLevenshteinDistance() << std::endl;
	computer.displayAlignment();
	computer.end ();
	return 0;
}
