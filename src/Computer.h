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

		// Prints the 2D array of the strings alignment score to the output
		// stream given as parameter.
		void PrintScore(std::ostream& out);
		void PrintBackTrack(std::ostream& out);
		void PrintAlignment(std::ostream& out);

		// Constructor
		// The two strings whose distance is to be computed are to be passed as
		// parameters, the order of the strings doesn't matter.
		Computer (const std::string& a, const std::string& b);

		// Destructor
		// Frees the memory assigned during the computation.
		~Computer ( );

	private:
		// Costs for the different strings modifications possible
		int MISMATCH_COST = 1;	// Character mismatch cost
		int INDEL_COST = 1;		// Character insertion cost
		int MATCH_COST = 0;		// Character match cost

		// Variables shared among procedures
		std::string a;			// first word
		std::string b;			// second word

		// Variables used in the alignment computation (PrintAlignment)
		char * firstAlignedString;		// string a transformed
		char * secondAlignedString;		// string b transformed
		int stringOutputSize = 0;		// aligned strings length

		int WIDTH;			// width of the score matrix = first word length + 1
		int HEIGHT;			// height of the score matrix = 2nd word length + 1

		Levenshtein::ScoreBack ** scoreBack;	// Score and backtrack matrix

		bool distanceComputed = false;		// Indicates if the distance
											// computation was done
		bool alignmentComputed = false;		// Indicates if the string
											// alignment was performed
		void computeScoreAndBacktrack ();
	};
}
