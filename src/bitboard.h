// bitboard set/get/pop macros
#define set_bit(bitboard, square) ((bitboard) |= (1ULL << (square)))
#define get_bit(bitboard, square) ((bitboard) & (1ULL << (square)))
#define pop_bit(bitboard, square) ((bitboard) &= (1ULL << (square)))

namespace Frogboard {

void print_bitboard(const U64 bitboard);

}

