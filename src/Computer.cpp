#include <stack>

#include "Computer.h"

namespace Levenshtein
{

	void Computer::PrintScore (std::ostream& out)
	{
		if ( !distanceComputed )
		{
			computeScoreAndBacktrack();
		}

		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				std::cout << scoreBack[j][i].score << " ";
			}
			std::cout << std::endl ;
		}
	}

	void Computer::PrintBackTrack (std::ostream& out)
	{
		if ( !distanceComputed )
		{
			computeScoreAndBacktrack();
		}

		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				std::cout << scoreBack[j][i].back << " ";
			}
			std::cout << std::endl ;
		}
	}

	void Levenshtein::Computer::PrintAlignment (std::ostream& out)
	{
		if ( !distanceComputed )
		{
			computeScoreAndBacktrack();
		}


		if ( !alignmentComputed )
		{	// If the string alignment was not already computed, it is done once
			std::stack <char> action;
			int i = WIDTH-1;
			int j = HEIGHT-1;
			while ( i != 0 || j != 0)
			{
				action.push(scoreBack[i][j].back);
				//std::cout << action.top() << std::endl;
				switch (action.top())
				{
					case Levenshtein::DIAGONAL:
						i--;
						j--;
					break;
					case Levenshtein::TOP :
						j--;
					break;
					case Levenshtein::LEFT :
						i--;
					break;
				}
			}

			stringOutputSize = action.size();
#ifdef DEBUG
			std::cerr << "Alignment length:" << action.size() << std::endl;
#endif
			firstAlignedString = new char [stringOutputSize];
			secondAlignedString = new char [stringOutputSize];
			int k = 0;

			while ( !action.empty() )
			{
				switch (action.top())
				{
					case Levenshtein::DIAGONAL:
						firstAlignedString[k] = a[i];
						secondAlignedString[k] = b[j];
						i++;
						j++;
					break;
					case Levenshtein::TOP :
						firstAlignedString[k] = '-';
						secondAlignedString[k] = b[j];
						j++;
					break;
					case Levenshtein::LEFT :
						firstAlignedString[k] = a[i];
						secondAlignedString[k] = '-';
						i++;
					break;
				}
				action.pop();
				k++;
			}
		}

		// Printing the string alignment
		for (int z = 0; z < stringOutputSize; z++) {
			out << firstAlignedString[z];
		}
		std::cout << std::endl;
		for (int z = 0; z < stringOutputSize; z++) {
			out << secondAlignedString[z];
		}
		out << std::endl;
	}

	void Computer::computeScoreAndBacktrack ()
	{
		int i; 		// ith column
		int j;		// jth line

		// Computing the first column
		for (i = 0, j = 1; j < HEIGHT; j++)
		{
			scoreBack [i][j].score = scoreBack [i][j-1].score + INDEL_COST;
			scoreBack [i][j].back = TOP;
		}
		// Computing the first line
		for (i = 1, j = 0; i < WIDTH; i++)
		{
			scoreBack [i][j].score = scoreBack [i-1][j].score + INDEL_COST;
			scoreBack [i][j].back = LEFT;
		}

		// Computing the rest of the score
		for (i = 1; i < WIDTH; i++)
		{
			for (j = 1; j < HEIGHT; j++) {
				// Compute the three candidates
				int top = scoreBack [i][j-1].score + INDEL_COST;

				int left = scoreBack [i-1][j].score + INDEL_COST;

				int topLeft;
				if ( a[i-1] == b[j-1] )
				{
					topLeft = scoreBack [i-1][j-1].score + MATCH_COST;
				} else {
					topLeft = scoreBack [i-1][j-1].score + MISMATCH_COST;
				}
#ifdef DEBUG
				std::cerr << "Top:" << top << " Diag:" << topLeft << " Left:"
						<< left;
#endif
				// Pick the highest value of them three
				Backtrack back = TOP;
				if ( left < top )
				{
					top = left;
					back = LEFT;
				}
				if ( topLeft < top )
				{
					top = topLeft;
					back = DIAGONAL;
				}
				scoreBack [i][j].score = top;
				scoreBack [i][j].back = back;
#ifdef DEBUG
				std::cerr << " BEST:" << scoreBack [i][j].score << " BACK:" <<
						scoreBack[i][j].back << std::endl;
#endif
			}
		}
		distanceComputed = true;
	}



	int Computer::Distance ( )
	{
		if ( ! distanceComputed )
		{
			computeScoreAndBacktrack();
		}
		return scoreBack[WIDTH-1][HEIGHT-1].score;
	}

//--------------------------CONSTRUCTORS AND DESTRUCTORS------------------------

	// Constructor
	//	first : first string to be copied in the class's attributes
	//	second : second string to be copied in the class's attributes
	Computer::Computer (const std::string& first, const std::string& second) :
		a (first), b (second), WIDTH (a.length() + 1), HEIGHT (b.length() + 1)
	{
		scoreBack = new Levenshtein::ScoreBack * [ WIDTH ];	//Score matrix
		for (int i = 0; i < WIDTH; i++)
		{
			scoreBack [ i ] = new ScoreBack [ HEIGHT ];
		}
		scoreBack [0][0].score = 0;
		scoreBack [0][0].back = ROOT;
	}

	// Destructor
	Computer::~Computer ( )
	{
		if ( distanceComputed )
		{
			for (int i = 0; i < WIDTH; i++)
			{
				delete[] scoreBack [ i ];
			}
			delete[] scoreBack;
		}
		if ( alignmentComputed )
		{
			delete firstAlignedString;
			delete secondAlignedString;
		}
	}
}
