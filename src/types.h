#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#define U32 unsigned long
#define U64 unsigned long long

#include <cassert>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <algorithm>

constexpr int MAX_MOVES = 256;
constexpr int MAX_PLY = 246;

// Moves are stored as 64-bit numbers
//
// bit 0-5: destination square (0-63)
// bit 6-11: origin square (0-63)
// bit 12-13: promotion piece type - (0: KNIGHT, 1: BISHOP, 2: ROOK, 3: QUEEN)
// bit 14-15: special move flags (1: promotion, 2: en passant, 3: castling)
// NOTE: en passant bit is set only when a pawn can be captured
//
// Special cases are MOVE_NONE and MOVE_NULL. Any normal move will always
// have different destination square and origin square. We sneak MOVE_NONE
// and MOVE_NULL in in cases where destination square and origin square are equal

enum Move: int {
	MOVE_NONE,
	MOVE_NULL = 65
};

enum MoveType {
	NORMAL,
	PROMOTION = 1 << 14,
	EN_PASSANT = 2 << 14,
	CASTLING = 3 << 14
};

enum Color {
	WHITE, BLACK, COLOR_NB = 2
};

enum CastlingSide {
	KING_SIDE, QUEEN_SIDE, CASTLING_SIDE_NB = 2
};

enum CastlingRight {
	NO_CASTLING,
	WHITE_OO,
	WHITE_OOO = WHITE_OO << 1,
	BLACK_OO = WHITE_OO << 2,
	BLACK_OOO = WHITE_OO << 3,

	WHITE_CASTLING = WHITE_OO | WHITE_OOO,
	BLACK_CASTLING = BLACK_OO | BLACK_OOO,
	ANY_CASTLING = WHITE_CASTLING | BLACK_CASTLING,

	CASTLING_RIGHT_NB = 16
};

enum Value : int {
	VALUE_ZERO      = 0,
	VALUE_DRAW      = 0,
	VALUE_KNOWN_WIN = 10000,
	VALUE_MATE      = 32000,
	VALUE_INFINITE  = 32001,
	VALUE_NONE      = 32002,

	VALUE_TB_WIN_IN_MAX_PLY = VALUE_MATE - 2 * MAX_PLY,
	VALUE_TB_LOSS_IN_MAX_PLY = - VALUE_TB_WIN_IN_MAX_PLY,
	VALUE_MATE_IN_MAX_PLY = VALUE_MATE - MAX_PLY,
	VALUE_MATED_IN_MAX_PLY = -VALUE_MATE_IN_MAX_PLY,

	PawnValueMg   = 126, PawnValueEg    = 208,
	KnightValueMg = 781,  KnightValueEg = 854,
	BishopValueMg = 825,  BishopValueEg = 915,
	RookValueMg   = 1276, RookValueEg   = 1380,
	QueenValueMg  = 2538, QueenValueEg  = 2682,

	MidgameLimit  = 15258, EndgameLimit = 3915
};


enum PieceType {
	NO_PIECE_TYPE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING,
	ALL_PIECES = -1,
	PIECE_TYPE_NB = 7
};

enum Piece {
	NO_PIECE,
	W_PAWN = 0, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
	B_PABN = 8, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
	PIECE_NB = 16
};

enum Square : int {
	SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
	SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
	SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
	SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
	SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
	SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
	SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
	SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
	SQ_NONE,

	SQUARE_NB = 64
};

enum Direction : int {
	NORTH = 8,
	EAST = 1,
	SOUTH = - NORTH,
	WEST = - EAST,

	NORTH_EAST = NORTH + EAST,
	NORTH_WEST = NORTH + WEST,
	SOUTH_EAST = SOUTH + EAST,
	SOUTH_WEST = SOUTH + WEST
};

enum File : int {
	FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NB
};

enum Rank : int {
	RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NB
};

constexpr Square make_square(File f, Rank r) {
	return Square((r << 3) + f);
}

constexpr Piece make_piece(Color c, PieceType pt) {
	return Piece((c << 3) + pt);
}

inline Color color_of(Piece pc) {
	assert(pc != NO_PIECE);
	return Color(pc >> 3);
}

constexpr PieceType type_of(Piece pc) {
	return PieceType(pc & 7);
}

constexpr bool is_ok(Square s) {
	return s >= SQ_A1 && s <= SQ_H8;
}

constexpr File file_of(Square s) {
	return File(s & 7);
}

constexpr Rank rank_of(Square s) {
	return Rank(s >> 3);
}

constexpr Direction pawn_push(Color c) {
	return c == WHITE ? NORTH : SOUTH;
}

constexpr Square from_sq(Move m) {
	return Square((m >> 6) & 0x3F);
}

constexpr Square to_sq(Move m) {
	return Square(m & 0x3F);
}

constexpr int from_to(Move m) {
	return m & 0xFFF;
}

constexpr MoveType type_of(Move m) {
	return MoveType(m & (3 << 14));
}

constexpr PieceType promotion_type(Move m) {
	return PieceType(((m >> 12) & 3) + KNIGHT);
}

constexpr Move make_move(Square from, Square to) {
	return Move((from << 6) + to);
}

constexpr bool is_ok(Move m) {
	return from_sq(m) != to_sq(m); // Catch MOVE_NULL and MOVE_NONE
}

#endif

