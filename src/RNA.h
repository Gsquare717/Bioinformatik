#ifndef BIOINFOI_RNA_H
#define BIOINFOI_RNA_H

namespace Alphabet
{

/**
 * Class implementing the conversion and validation
 * of string charactes to sequence characters
 */
class RNA
{
  public:
	/// The characters available for RNA
	enum class Characters { A, C, G, U };

	/**
	 * Converts a char to a Character. The conversion is case insensitive.
	 * Throws an InvalidCharacter exception if the passed char is invalid.
	 */
	static Characters toCharacter(char c);

	/**
	 * Converts a Character to an upper-case char.
	 */
	static char toChar(Characters c);

	/**
	 * Converts the Character to an upper-case Character.
	*/
	static Characters canonicalize(Characters c);
};
}

#endif // BIOINFOI_RNA_H
