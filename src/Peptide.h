#ifndef BIOINFOI_PEPTIDE_H
#define BIOINFOI_PEPTIDE_H

namespace Alphabet
{

/**
 * Class implementing the conversion and validation
 * of string charactes to sequence characters
 */
class Peptide
{
  public:
	/// The characters available for a Peptide
	enum class Characters {
		A,
		R,
		N,
		D,
		C,
		Q,
		E,
		G,
		H,
		I,
		L,
		K,
		M,
		F,
		P,
		S,
		T,
		W,
		Y,
		V
	};

	/**
	 * Converts a char to a Character. The conversion is case insensitive.
	 * Throws an InvalidCharacter exception if the passed char is invalid.
	 */
	static Characters toCharacter(char c);

	/**
	 * Converts a Character to an upper-case char.
	 */
	static char toChar(Characters c);

	static Characters canonicalize(Characters c) { return c; }
};
}

#endif // BIOINFOI_Peptide_H
