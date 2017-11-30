#include <iostream>
#include <string>
#include <stack>

#include "Computer.h"


//----------------------------------VARIABLES-----------------------------------


//----------------------------PROCEDURE DECLARATIONS----------------------------


//-----------------------------------MAIN---------------------------------------
int main (void)
{
	std::string a,b;
	getline(std::cin,a);
	getline(std::cin,b);
	Levenshtein::Computer computer (a,b);

#ifdef DEBUG
	computer.PrintScore(std::cerr);
	computer.PrintBackTrack(std::cerr);
#endif

	std::cout << computer.Distance() << std::endl;
	computer.PrintAlignment(std::cout);
	return 0;
}
