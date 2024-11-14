#include "Peptide.h"

#include "InvalidCharacter.h"

#include <cassert>

namespace Alphabet
{
Peptide::Characters Peptide::toCharacter(char c)
{
	switch (c) {
		case 'A':
		case 'a':
			return Characters::A;
		case 'R':
		case 'r':
			return Characters::R;
		case 'N':
		case 'n':
			return Characters::N;
		case 'D':
		case 'd':
			return Characters::D;
		case 'C':
		case 'c':
			return Characters::C;
		case 'Q':
		case 'q':
			return Characters::Q;
		case 'E':
		case 'e':
			return Characters::E;
		case 'G':
		case 'g':
			return Characters::G;
		case 'H':
		case 'h':
			return Characters::H;
		case 'I':
		case 'i':
			return Characters::I;
		case 'L':
		case 'l':
			return Characters::L;
		case 'K':
		case 'k':
			return Characters::K;
		case 'M':
		case 'm':
			return Characters::M;
		case 'F':
		case 'f':
			return Characters::F;
		case 'P':
		case 'p':
			return Characters::P;
		case 'S':
		case 's':
			return Characters::S;
		case 'T':
		case 't':
			return Characters::T;
		case 'W':
		case 'w':
			return Characters::W;
		case 'Y':
		case 'y':
			return Characters::Y;
		case 'V':
		case 'v':
			return Characters::V;
		default:
			throw InvalidCharacter(c);
	}
}

char Peptide::toChar(Peptide::Characters c)
{
	switch (c) {
		case Characters::A:
			return 'A';
		case Characters::R:
			return 'R';
		case Characters::N:
			return 'N';
		case Characters::D:
			return 'D';
		case Characters::C:
			return 'C';
		case Characters::Q:
			return 'Q';
		case Characters::E:
			return 'E';
		case Characters::G:
			return 'G';
		case Characters::H:
			return 'H';
		case Characters::I:
			return 'I';
		case Characters::L:
			return 'L';
		case Characters::K:
			return 'K';
		case Characters::M:
			return 'M';
		case Characters::F:
			return 'F';
		case Characters::P:
			return 'P';
		case Characters::S:
			return 'S';
		case Characters::T:
			return 'T';
		case Characters::W:
			return 'W';
		case Characters::Y:
			return 'Y';
		case Characters::V:
			return 'V';
	}

	assert("Unhandled character in Peptide::toCharacter" && false);
}
}
