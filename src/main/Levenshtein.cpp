#include <iostream>
#include <string>
#include <stack>

#include "Computer.h"


//----------------------------------VARIABLES-----------------------------------


//----------------------------PROCEDURE DECLARATIONS----------------------------


//-----------------------------------MAIN---------------------------------------
int main (void)
{
	init ();
	computeScoreAndBacktrack();

#ifdef DEBUG
	displayScore();
	displayBackTrack();
#endif

	std::cout << "Score:" << scoreBack[WIDTH-1][HEIGHT-1].score << std::endl;
	displayAlignment();
	end ();
	return 0;
}
