#include <iostream>

#include "types.h"
#include "bitboard.h"

namespace Frogboard {

void print_bitboard(const U64 bitboard) {
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file < 8; file++) {
			int square = rank * 8 + file;

			std::cout << " " << (get_bit(bitboard, square) ? 1 : 0) << " ";
		}

		// print newline for every rank
		std::cout << std::endl;
	}
}

} // Frogboard
