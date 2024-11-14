#include "DNA.h"
#include "InvalidCharacter.h"

#include <cassert>
#include <iostream>

namespace Alphabet
{
DNA::Characters DNA::toCharacter(char c)
{
	switch (c) {
		case 'A':
			return Characters::A;
		case 'a':
			return Characters::a;
		case 'T':
			return Characters::T;
		case 't':
			return Characters::t;
		case 'G':
			return Characters::G;
		case 'g':
			return Characters::g;
		case 'C':
			return Characters::C;
		case 'c':
			return Characters::c;
		case 'N':
		case 'n':
			return Characters::N;
		default:
			throw InvalidCharacter(c);
	}
}

char DNA::toChar(DNA::Characters c)
{
	switch (c) {
		case Characters::A:
			return 'A';
		case Characters::a:
			return 'a';
		case Characters::T:
			return 'T';
		case Characters::t:
			return 't';
		case Characters::G:
			return 'G';
		case Characters::g:
			return 'g';
		case Characters::C:
			return 'C';
		case Characters::c:
			return 'c';
		default:
			return 'N';	
	}

	assert("Unhandled character in DNA::toChar" && false);
}

DNA::Characters DNA::canonicalize(DNA::Characters c)
{
	switch(c) {
		case Characters::a:
			return Characters::A;
		case Characters::t:
			return Characters::T;
		case Characters::g:
			return Characters::G;
		case Characters::c:
			return Characters::C;
		default:
			return c;
	}
}

}