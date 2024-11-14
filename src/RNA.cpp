#include "RNA.h"

#include "InvalidCharacter.h"

#include <cassert>

namespace Alphabet
{
RNA::Characters RNA::toCharacter(char c)
{
	switch (c) {
		case 'A':
		case 'a':
			return Characters::A;
		case 'U':
		case 'u':
			return Characters::U;
		case 'G':
		case 'g':
			return Characters::G;
		case 'C':
		case 'c':
			return Characters::C;
		default:
			throw InvalidCharacter(c);
	}
}

char RNA::toChar(RNA::Characters c)
{
	switch (c) {
		case Characters::A:
			return 'A';
		case Characters::U:
			return 'U';
		case Characters::G:
			return 'G';
		case Characters::C:
			return 'C';
	}

	assert("Unhandled character in RNA::toCharacter" && false);
}

RNA::Characters RNA::canonicalize(Characters c)
{
	return c;
}
}
