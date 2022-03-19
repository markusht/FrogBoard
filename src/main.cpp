#include <iostream>

#include "misc.h"
#include "bitboard.h"

using namespace Frogboard;

int main(int argc, char* argv[]) {
	std::cout << engine_info() << std::endl;

	// piece bitboards
	U64 bitboards[12];

	// occupancy bitboards
	U64 occupancies[3];

	U64 bitboardTester = 0;
	set_bit(bitboardTester, 3);

	print_bitboard(bitboardTester);

	return 0;
}
