#include "pch.h"
#include "CppUnitTest.h"
#include<graphics.h>
#include <stdio.h>
#include <windows.h>
#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
void load_image();
void game_init();
//按钮相关
bool in_range_white_change_skin(MOUSEMSG m_mouse);
bool in_range_black_change_skin(MOUSEMSG m_mouse);
bool in_range_reset(MOUSEMSG m_mouse);
bool in_range_change_skin_1(MOUSEMSG m_mouse);
bool in_range_change_skin_2(MOUSEMSG m_mouse);
bool in_range_change_skin_3(MOUSEMSG m_mouse);
bool in_range_change_skin_4(MOUSEMSG m_mouse);
bool in_range_change_skin_5(MOUSEMSG m_mouse);
bool in_range_change_skin_6(MOUSEMSG m_mouse);
bool in_range_set_chess(MOUSEMSG m_mouse);
bool in_range_return(MOUSEMSG m_mouse);
bool in_range_record_end(MOUSEMSG m_mouse);
bool in_range_replay(MOUSEMSG m_mouse);
bool in_range_withdraw(MOUSEMSG m_mouse);
bool in_range_record(MOUSEMSG m_mouse);
//逻辑相关
void set_chess(MOUSEMSG m_mouse, int& play_side_now);
void withdraw();
void wait_mouse_click();
void draw_chess_board(int chess_board[][15]);
int is_five(int row, int column, int which_side);
bool is_one_side_win(int which_side);
void win(int which_side);
void save_game_record();
void show_skin();
void play();
void game_reset();
void game_replay();
int chose_skin();
void white_skin_change();
void black_skin_change();
void after_win_action();
extern int chess_board[15][15];
//棋盘范围
#define CHESS_UP 98
#define CHESS_DOWN 772
#define CHESS_LEFT 207
#define CHESS_RIGHT 906
//悔棋按钮范围
#define WITHDRAW_UP 35
#define WITHDRAW_DOWN 73
#define WITHDRAW_LEFT 331
#define WITHDRAW_RIGHT 425
//中途记录对局按钮范围
#define RECORD_UP 35
#define RECORD_DOWN 73
#define RECORD_LEFT 509
#define RECORD_RIGHT 601
//返回菜单按钮范围
#define RETURN_UP 400
#define RETURN_DOWN 584
#define RETURN_LEFT 285
#define RETURN_RIGHT 441
//结束时记录对局按钮范围
#define RECORD_END_UP 400
#define RECORD_END_DOWN 584
#define RECORD_END_LEFT 475
#define RECORD_END_RIGHT 634
//精彩重播按钮范围
#define REPLAY_UP 400
#define REPLAY_DOWN 584
#define REPLAY_LEFT 674
#define REPLAY_RIGHT 821
//白色方换皮肤按钮
#define WHITE_CHANGE_SKIN_UP 366
#define WHITE_CHANGE_SKIN_DOWN 404
#define WHITE_CHANGE_SKIN_LEFT 31
#define WHITE_CHANGE_SKIN_RIGHT 144
//黑色方换皮肤按钮
#define BLACK_CHANGE_SKIN_UP 367
#define BLACK_CHANGE_SKIN_DOWN 403
#define BLACK_CHANGE_SKIN_LEFT 969
#define BLACK_CHANGE_SKIN_RIGHT 1062 
//重来按钮
#define RESET_UP 36
#define RESET_DOWN 73
#define RESET_LEFT 683
#define RESET_RIGHT 778 
//换皮肤1按钮
#define CHANGE_SKIN_1_UP (pic_y+47)
#define CHANGE_SKIN_1_DOWN (pic_y+47+chess_icon_size)
#define CHANGE_SKIN_1_LEFT (pic_x+38)
#define CHANGE_SKIN_1_RIGHT (pic_x+38+chess_icon_size)
//换皮肤2按钮
#define CHANGE_SKIN_2_UP (pic_y+47)
#define CHANGE_SKIN_2_DOWN (pic_y+47+chess_icon_size)
#define CHANGE_SKIN_2_LEFT (pic_x+189)
#define CHANGE_SKIN_2_RIGHT (pic_x+189+chess_icon_size)
//换皮肤3按钮
#define CHANGE_SKIN_3_UP (pic_y+47)
#define CHANGE_SKIN_3_DOWN (pic_y+47+chess_icon_size)
#define CHANGE_SKIN_3_LEFT (pic_x+337)
#define CHANGE_SKIN_3_RIGHT (pic_x+337+chess_icon_size)
//换皮肤4按钮
#define CHANGE_SKIN_4_UP (pic_y+182)
#define CHANGE_SKIN_4_DOWN (pic_y+182+chess_icon_size)
#define CHANGE_SKIN_4_LEFT (pic_x+38)
#define CHANGE_SKIN_4_RIGHT (pic_x+38+chess_icon_size)
//换皮肤5按钮
#define CHANGE_SKIN_5_UP (pic_y+182)
#define CHANGE_SKIN_5_DOWN (pic_y+182+chess_icon_size)
#define CHANGE_SKIN_5_LEFT (pic_x+187)
#define CHANGE_SKIN_5_RIGHT (pic_x+187+chess_icon_size)
//换皮肤6按钮
#define CHANGE_SKIN_6_UP (pic_y+182)
#define CHANGE_SKIN_6_DOWN (pic_y+182+chess_icon_size)
#define CHANGE_SKIN_6_LEFT (pic_x+343)
#define CHANGE_SKIN_6_RIGHT (pic_x+343+chess_icon_size)
const int BLACK_CHESS = 1;
const int WHITE_CHESS = -1;
const int EMPTY = 0;
enum which_rival {
	HUMAN, AI
};
enum which_side {
	WHITE_SIDE, BLACK_SIDE//分别是白方下棋和黑方下棋
};
enum which_page {
	GAME_PAGE, SKIN_PAGE, WIN_PAGE
};
struct point {
	int x = 0;
	int y = 0;
};
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace change_skin_test
{
	TEST_CLASS(change_skin_success)
	{
	public:
		
		TEST_METHOD(white_skin_change_success)
		{
			MOUSEMSG m_mouse;
			m_mouse.x = 100;
			m_mouse.y = 200;
			bool result = in_range_white_change_skin(m_mouse);
			Assert::AreEqual(false,result);
		}
		TEST_METHOD(black_skin_change_success)
		{
			MOUSEMSG m_mouse;
			m_mouse.x = 100;
			m_mouse.y = 200;
			bool result = in_range_black_change_skin(m_mouse);
			Assert::AreEqual(false,result);
		}

	};
	
	TEST_CLASS(change_skin_fail)
	{
	public:
		
		TEST_METHOD(white_skin_change_fail)
		{
			MOUSEMSG m_mouse;
			m_mouse.x = 100;
			m_mouse.y = 200;
			bool result = in_range_white_change_skin(m_mouse);
			Assert::AreEqual(false,result);
			return;
		}
		TEST_METHOD(black_skin_change_fail)
		{
			MOUSEMSG m_mouse;
			m_mouse.x = 100;
			m_mouse.y = 200;
			bool result = in_range_black_change_skin(m_mouse);
			Assert::AreEqual(false,result);
			return;
		}

	};
}
namespace is_win_test 
{
	TEST_CLASS(white_win_success) {
		TEST_METHOD(test1) {
			memset(chess_board, -1 , sizeof(chess_board));
			bool result = is_one_side_win(WHITE_SIDE);
			Assert::AreEqual(true, result);
		}
		TEST_METHOD(test2) {
			int test[15][15] = {
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			};
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {
					chess_board[i][j] = test[i][j];
				}
			}
			bool result = is_one_side_win(WHITE_SIDE);
			Assert::AreEqual(true, result);
		}
	};

}