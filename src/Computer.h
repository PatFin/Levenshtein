#include <iostream>
#include <string>

#include "Types.h"
// Namespace for types used in the Levenshtein distance computation
namespace Levenshtein
{
	class Computer
	{
	public:

		// Returns the distance between the strings considered by this instance
		// of the problem solver.
		int Distance ( );

		// TODO Original methods to be changed
		void init (std::string& a, std::string& b);

		void end();
		void displayScore();
		void displayBackTrack();
		void computeScoreAndBacktrack();
		void displayAlignment();

		int GetLevenshteinDistance ();
	private:
		// Costs for the different strings modifications possible
		int MISMATCH_COST = 1;	// Character mismatch cost
		int INDEL_COST = 1;		// Character insertion cost
		int MATCH_COST = 0;		// Character match cost

		// Variables shared among procedures
		std::string a;			// first word
		std::string b;			// second word

		int WIDTH;			// width of the score matrix = first word length + 1
		int HEIGHT;			// height of the score matrix = 2nd word length + 1

		Levenshtein::ScoreBack ** scoreBack;	// Score and backtrack matrix

		bool distanceComputed = false;
	};
}
