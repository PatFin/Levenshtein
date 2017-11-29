#include <iostream>
#include <string>
#include <stack>

// Namespace for types used in the Levenshtein distance computation
namespace Levenshtein
{
	typedef char Backtrack;
	// Backtrack characters
	static const Backtrack ROOT = 'R';
	static const Backtrack TOP = 'T';
	static const Backtrack LEFT = 'L';
	static const Backtrack DIAGONAL = 'D';

	// Costs for the different modifications possible
	static const int MISMATCH_COST = -1;
	static const int INDEL_COST = -1;
	static const int MATCH_COST = 1;

	class ScoreBack
	{
		public :

		int score;
		Backtrack back;

		void setRoot ( )
		{
			score = 0;
			back = ROOT;
		}
	};
}
//---------------------- PARAMETERS OF THE ALGORITHM ---------------------------

//----------------------------------VARIABLES-----------------------------------
// Variables shared among procedures
std::string a;			// first word
std::string b;			// second word

int WIDTH;			// width of the score matrix = first word length + 1
int HEIGHT;			// height of the score matrix = 2nd word length + 1

Levenshtein::ScoreBack ** scoreBack;	// Score and backtrack matrix

//----------------------------PROCEDURE DECLARATIONS----------------------------
void init ();
void end();
void displayScore();
void displayBackTrack();
void computeScoreAndBacktrack();
void displayAlignment();
//---------------------------------PROCEDURES-----------------------------------
void init ( )
{
	getline(std::cin,a);
	getline(std::cin,b);

	WIDTH = a.length() + 1;
	HEIGHT = b.length() + 1;

	scoreBack = new Levenshtein::ScoreBack * [ WIDTH ];	//Score matrix
	for (int i = 0; i < WIDTH; i++)
	{
		scoreBack [ i ] = new Levenshtein::ScoreBack [ HEIGHT ];
	}
	scoreBack [0][0].setRoot();
}

void end ( )
{
	for (int i = 0; i < WIDTH; i++)
	{
		delete[] scoreBack [ i ];
	}
	delete[] scoreBack;
}

void displayScore ()
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

void displayBackTrack ()
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

void computeScoreAndBacktrack ()
{
	int i; 		// ith column
	int j;		// jth line

	// Computing the first column
	for (i = 0, j = 1; j < HEIGHT; j++)
	{
		scoreBack [i][j].score = scoreBack [i][j-1].score +
			Levenshtein::INDEL_COST;
		scoreBack [i][j].back = Levenshtein::TOP;
	}
	// Computing the first line
	for (i = 1, j = 0; i < WIDTH; i++)
	{
		scoreBack [i][j].score = scoreBack [i-1][j].score +
			Levenshtein::INDEL_COST;
		scoreBack [i][j].back = Levenshtein::LEFT;
	}

	// Computing the rest of the score
	for (i = 1; i < WIDTH; i++)
	{
		for (j = 1; j < HEIGHT; j++) {
			// Compute the three candidates
			int top = scoreBack [i][j-1].score + Levenshtein::INDEL_COST;

			int left = scoreBack [i-1][j].score + Levenshtein::INDEL_COST;

			int topLeft;
			if ( a[i-1] == b[j-1] )
			{
				topLeft = scoreBack [i-1][j-1].score + Levenshtein::MATCH_COST;
			} else {
				topLeft = scoreBack [i-1][j-1].score +
						Levenshtein::MISMATCH_COST;
			}
			#ifdef DEBUG
			std::cout << "Top:" << top << " Diag:" << topLeft << " Left:"
					<< left;
			#endif
			// Pick the highest value of them three
			char back = Levenshtein::TOP;
			if (top < left)
			{
				top = left;
				back = Levenshtein::LEFT;
			}
			if ( top < topLeft )
			{
				top = topLeft;
				back = Levenshtein::DIAGONAL;
			}
			scoreBack [i][j].score = top;
			scoreBack [i][j].back = back;
			#ifdef DEBUG
			std::cout << " BEST:" << scoreBack [i][j].score << " BACK:" <<
					scoreBack[i][j].back << std::endl;
			#endif
		}
	}
}

void displayAlignment ( )
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
