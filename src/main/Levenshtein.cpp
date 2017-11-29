#include <iostream>
#include <string>
#include <stack>

using namespace std;


namespace Levenshtein
{
	typedef char Backtrack;
	class ScoreBack
	{
		public :
		// Backtrack characters
		static const Backtrack ROOT = 'R';
		static const Backtrack TOP = 'T';
		static const Backtrack LEFT = 'L';
		static const Backtrack DIAGONAL = 'D';

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
// Costs for the different modifications possible
const int MISMATCH_COST = -1;
const int INDEL_COST = -1;
const int MATCH_COST = 1;

//----------------------------------VARIABLES-----------------------------------
// Variables shared among procedures
string a;			// first word
string b;			// second word

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
	getline(cin,a);
	getline(cin,b);

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
			cout << scoreBack[j][i].score << " ";
		}
		cout << endl ;
	}
}

void displayBackTrack ()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			cout << scoreBack[j][i].back << " ";
		}
		cout << endl ;
	}
}

void computeScoreAndBacktrack ()
{
	int i; 		// ith column
	int j;		// jth line

	// Computing the first column
	for (i = 0, j = 1; j < HEIGHT; j++)
	{
		scoreBack [i][j].score = scoreBack [i][j-1].score + INDEL_COST;
		scoreBack [i][j].back = Levenshtein::ScoreBack::TOP;
	}
	// Computing the first line
	for (i = 1, j = 0; i < WIDTH; i++)
	{
		scoreBack [i][j].score = scoreBack [i-1][j].score + INDEL_COST;
		scoreBack [i][j].back = Levenshtein::ScoreBack::LEFT;
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
				topLeft = scoreBack [i-1][j-1].score + INDEL_COST;
			}
			#ifdef DEBUG
			cout << "Top:" << top << " Diag:" << topLeft << " Left:" << left;
			#endif
			// Pick the highest value of them three
			char back = Levenshtein::ScoreBack::TOP;
			if (top < left)
			{
				top = left;
				back = Levenshtein::ScoreBack::LEFT;
			}
			if ( top < topLeft )
			{
				top = topLeft;
				back = Levenshtein::ScoreBack::DIAGONAL;
			}
			scoreBack [i][j].score = top;
			scoreBack [i][j].back = back;
			#ifdef DEBUG
			cout << " BEST:" << scoreBack [i][j].score << " BACK:" <<
					scoreBack[i][j].back << endl;
			#endif
		}
	}
}

void displayAlignment ( )
{

	stack <char> action;
	int i = WIDTH-1;
	int j = HEIGHT-1;
	while ( i != 0 || j != 0)
	{
		action.push(scoreBack[i][j].back);
		//cout << action.top() << endl;
		switch (action.top())
		{
			case Levenshtein::ScoreBack::DIAGONAL:
				i--;
				j--;
			break;
			case Levenshtein::ScoreBack::TOP :
				j--;
			break;
			case Levenshtein::ScoreBack::LEFT :
				i--;
			break;
		}
	}

	int stringOutputSize = action.size();
#ifdef DEBUG
	cout << "Alignment length:" << action.size() << endl;
#endif
	char x [stringOutputSize];
	char y [stringOutputSize];
	int k = 0;

	while ( !action.empty() )
	{
		switch (action.top())
		{
			case Levenshtein::ScoreBack::DIAGONAL:
				x[k] = a[i];
				y[k] = b[j];
				i++;
				j++;
			break;
			case Levenshtein::ScoreBack::TOP :
				x[k] = '-';
				y[k] = b[j];
				j++;
			break;
			case Levenshtein::ScoreBack::LEFT :
				x[k] = a[i];
				y[k] = '-';
				i++;
			break;
		}
		action.pop();
		k++;
	}


	for (int z = 0; z < stringOutputSize; z++) {
		cout << x[z];
	}
	cout << endl;
	for (int z = 0; z < stringOutputSize; z++) {
		cout << y[z];
	}
	cout << endl;
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

	cout << "Score:" << scoreBack[WIDTH-1][HEIGHT-1].score << endl;
	displayAlignment();
	end ();
	return 0;
}
