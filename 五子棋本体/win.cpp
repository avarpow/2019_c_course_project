#include "new.h"
#include "win.h"
extern int chess_board[15][15];
int is_five(int row, int column, int which_side)
{
    int i, j, k = 0, p[4] = { 0, -1, -1, -1 }, q[4] = {1,1,0,-1,},chess_count = 0, z = 0;
    if (which_side == WHITE_SIDE) {
        z = -1;
    } else if (which_side == BLACK_SIDE) {
        z = 1;
    }
    for (i = 0; i < 4; i++) {
        for (j = -4; j <= 4 && (row + p[i] * j) < 15 && (row + p[i] * j) >= 0 && (column + q[i] * j) < 15 && (column + q[i] * j) >= 0; j++) {
            if (chess_board[row + p[i] * j][column + q[i] * j] != z)
                chess_count = 0;
            else
                chess_count++;
            if (chess_count == 5)
                k = 1;
        }
    }
    return k;
}
bool is_one_side_win(int which_side)
{
    if (which_side == WHITE_SIDE) {
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                if (is_five(i, j, WHITE_SIDE)) {
                    return true;
                }
            }
        }
    }
    if (which_side == BLACK_SIDE) {
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                if (is_five(i, j, BLACK_SIDE)) {
                    return true;
                }
            }
        }
    }
    return false;
}