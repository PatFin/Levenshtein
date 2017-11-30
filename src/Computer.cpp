#include <stack>

#include "Computer.h"

namespace Levenshtein
{


	void Computer::init (std::string& first, std::string& second)
	{
		a = first;
		b = second;

		WIDTH = a.length() + 1;
		HEIGHT = b.length() + 1;

		scoreBack = new Levenshtein::ScoreBack * [ WIDTH ];	//Score matrix
		for (int i = 0; i < WIDTH; i++)
		{
			scoreBack [ i ] = new ScoreBack [ HEIGHT ];
		}
		scoreBack [0][0].score = 0;
		scoreBack [0][0].back = ROOT;
	}

	void Computer::end ( )
	{
		for (int i = 0; i < WIDTH; i++)
		{
			delete[] scoreBack [ i ];
		}
		delete[] scoreBack;
	}

	void Levenshtein::Computer::displayScore ()
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				std::cout << scoreBack[j][i].score << " ";
			}
			std::cout << std::endl ;
		}
	}

	void Levenshtein::Computer::displayBackTrack ()
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				std::cout << scoreBack[j][i].back << " ";
			}
			std::cout << std::endl ;
		}
	}

	void Levenshtein::Computer::computeScoreAndBacktrack ()
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
				std::cout << "Top:" << top << " Diag:" << topLeft << " Left:"
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
				std::cout << " BEST:" << scoreBack [i][j].score << " BACK:" <<
						scoreBack[i][j].back << std::endl;
				#endif
			}
		}
		distanceComputed = true;
	}

	void Levenshtein::Computer::displayAlignment ( )
	{

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

		int stringOutputSize = action.size();
	#ifdef DEBUG
		std::cout << "Alignment length:" << action.size() << std::endl;
	#endif
		char x [stringOutputSize];
		char y [stringOutputSize];
		int k = 0;

		while ( !action.empty() )
		{
			switch (action.top())
			{
				case Levenshtein::DIAGONAL:
					x[k] = a[i];
					y[k] = b[j];
					i++;
					j++;
				break;
				case Levenshtein::TOP :
					x[k] = '-';
					y[k] = b[j];
					j++;
				break;
				case Levenshtein::LEFT :
					x[k] = a[i];
					y[k] = '-';
					i++;
				break;
			}
			action.pop();
			k++;
		}


		for (int z = 0; z < stringOutputSize; z++) {
			std::cout << x[z];
		}
		std::cout << std::endl;
		for (int z = 0; z < stringOutputSize; z++) {
			std::cout << y[z];
		}
		std::cout << std::endl;
	}

	int Computer::GetLevenshteinDistance ( )
	{
		if ( ! distanceComputed )
		{
			computeScoreAndBacktrack();
		}
		return scoreBack[WIDTH-1][HEIGHT-1].score;
	}
}
