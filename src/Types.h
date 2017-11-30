namespace Levenshtein
{
	typedef char Backtrack;
	// Backtrack characters
	static const Backtrack ROOT = 'R';
	static const Backtrack TOP = 'T';
	static const Backtrack LEFT = 'L';
	static const Backtrack DIAGONAL = 'D';

	struct ScoreBack
	{
		public :

		int score;
		Backtrack back;

	};
}
