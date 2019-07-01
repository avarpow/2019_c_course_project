#pragma once
#ifndef _NEW_
#define _NEW_
#include <conio.h>
#include <graphics.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <windows.h>
using namespace std;
void load_image();
void chose_rival();
void game_init();
bool in_range_vs_human(MOUSEMSG m_mouse);
bool in_range_vs_ai(MOUSEMSG m_mouse);
bool in_range_black_give_up(MOUSEMSG m_mouse);
bool in_range_white_give_up(MOUSEMSG m_mouse);
//��ť���
bool in_range_white_change_skin(MOUSEMSG m_mouse);
bool in_range_black_change_skin(MOUSEMSG m_mouse);
bool in_range_reset(MOUSEMSG m_mouse);
bool in_range_change_skin_1(MOUSEMSG m_mouse);
bool in_range_change_skin_2(MOUSEMSG m_mouse);
bool in_range_change_skin_3(MOUSEMSG m_mouse);
bool in_range_change_skin_4(MOUSEMSG m_mouse);
bool in_range_change_skin_5(MOUSEMSG m_mouse);
bool in_range_change_skin_6(MOUSEMSG m_mouse);
bool in_range_close(MOUSEMSG m_mouse);
bool in_range_set_chess(MOUSEMSG m_mouse);
bool in_range_return(MOUSEMSG m_mouse);
bool in_range_record_end(MOUSEMSG m_mouse);
bool in_range_replay(MOUSEMSG m_mouse);
bool in_range_withdraw(MOUSEMSG m_mouse);
bool in_range_record(MOUSEMSG m_mouse);
//�߼����
void set_chess(MOUSEMSG m_mouse, int& play_side_now);
void withdraw();
void wait_mouse_click();
void draw_chess_board(int chess_board[][15]);
int one_side_win(int which_side);
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
void points(int side, int sum);
void round(int sum);
//AI���

int Around(int x, int y); // ��Χ�Ƿ����Ӵ��ڣ����ӵľͼ��뿼��
int ScoreTable(int Number, int Empty);
// ���ֱ�
int CountScore(int n[], int turn); // �㵥�������
int Evaluate();
int Max_AlphaBeta(int Dep, int alpha, int beta); // �ֵ�AI����ʱ��AI����ѡ��
struct point MinMax_AlphaBeta(int Dep);
struct point aiTurn(int chess_board[15][15]);
void ai_set_chess();
void check_win();
int Min_AlphaBeta(int Dep, int alpha, int beta); // �ֵ���������ʱ����������ѡ��
//���˶�ս��Χ
#define VS_HUMAN_UP 449
#define VS_HUMAN_DOWN 552
#define VS_HUMAN_LEFT 278
#define VS_HUMAN_RIGHT 469
//�˻���ս��Χ
#define VS_AI_UP 452
#define VS_AI_DOWN 555
#define VS_AI_LEFT 679
#define VS_AI_RIGHT 875
//���̷�Χ
#define CHESS_UP 98
#define CHESS_DOWN 772
#define CHESS_LEFT 207
#define CHESS_RIGHT 906
//���尴ť��Χ
#define WITHDRAW_UP 35
#define WITHDRAW_DOWN 73
#define WITHDRAW_LEFT 331
#define WITHDRAW_RIGHT 425
//��;��¼�Ծְ�ť��Χ
#define RECORD_UP 35
#define RECORD_DOWN 73
#define RECORD_LEFT 509
#define RECORD_RIGHT 601
//���ز˵���ť��Χ
#define RETURN_UP 400
#define RETURN_DOWN 584
#define RETURN_LEFT 285
#define RETURN_RIGHT 441
//����ʱ��¼�Ծְ�ť��Χ
#define RECORD_END_UP 400
#define RECORD_END_DOWN 584
#define RECORD_END_LEFT 475
#define RECORD_END_RIGHT 634
//�����ز���ť��Χ
#define REPLAY_UP 400
#define REPLAY_DOWN 584
#define REPLAY_LEFT 674
#define REPLAY_RIGHT 821
//��ɫ����Ƥ����ť
#define BLACK_CHANGE_SKIN_UP 459
#define BLACK_CHANGE_SKIN_DOWN 503
#define BLACK_CHANGE_SKIN_LEFT 46
#define BLACK_CHANGE_SKIN_RIGHT 144
//��ɫ����Ƥ����ť
#define WHITE_CHANGE_SKIN_UP 460
#define WHITE_CHANGE_SKIN_DOWN 503
#define WHITE_CHANGE_SKIN_LEFT 969
#define WHITE_CHANGE_SKIN_RIGHT 1062
//��ɫ���䰴ť
#define BLACK_GIVE_UP_UP 551
#define BLACK_GIVE_UP_DOWN 594
#define BLACK_GIVE_UP_LEFT 46
#define BLACK_GIVE_UP_RIGHT 144
//��ɫ�����䰴ť
#define WHITE_GIVE_UP_UP 552
#define WHITE_GIVE_UP_DOWN 598
#define WHITE_GIVE_UP_LEFT 969
#define WHITE_GIVE_UP_RIGHT 1062
//���Ͱ�ť
#define ZAN_UP 637
#define ZAN_DOWN 685
#define ZAN_LEFT 46
#define ZAN_RIGHT 144
//���ڰ�ť
#define ABOUT_UP 637
#define ABOUT_DOWN 685
#define ABOUT_LEFT 969
#define ABOUT_RIGHT 1062
//������ť
#define RESET_UP 36
#define RESET_DOWN 73
#define RESET_LEFT 683
#define RESET_RIGHT 778
//��Ƥ��1��ť
#define CHANGE_SKIN_1_UP (pic_y + 47)
#define CHANGE_SKIN_1_DOWN (pic_y + 47 + chess_icon_size)
#define CHANGE_SKIN_1_LEFT (pic_x + 38)
#define CHANGE_SKIN_1_RIGHT (pic_x + 38 + chess_icon_size)
//��Ƥ��2��ť
#define CHANGE_SKIN_2_UP (pic_y + 47)
#define CHANGE_SKIN_2_DOWN (pic_y + 47 + chess_icon_size)
#define CHANGE_SKIN_2_LEFT (pic_x + 189)
#define CHANGE_SKIN_2_RIGHT (pic_x + 189 + chess_icon_size)
//��Ƥ��3��ť
#define CHANGE_SKIN_3_UP (pic_y + 47)
#define CHANGE_SKIN_3_DOWN (pic_y + 47 + chess_icon_size)
#define CHANGE_SKIN_3_LEFT (pic_x + 337)
#define CHANGE_SKIN_3_RIGHT (pic_x + 337 + chess_icon_size)
//��Ƥ��4��ť
#define CHANGE_SKIN_4_UP (pic_y + 182)
#define CHANGE_SKIN_4_DOWN (pic_y + 182 + chess_icon_size)
#define CHANGE_SKIN_4_LEFT (pic_x + 38)
#define CHANGE_SKIN_4_RIGHT (pic_x + 38 + chess_icon_size)
//��Ƥ��5��ť
#define CHANGE_SKIN_5_UP (pic_y + 182)
#define CHANGE_SKIN_5_DOWN (pic_y + 182 + chess_icon_size)
#define CHANGE_SKIN_5_LEFT (pic_x + 187)
#define CHANGE_SKIN_5_RIGHT (pic_x + 187 + chess_icon_size)
//��Ƥ��6��ť
#define CHANGE_SKIN_6_UP (pic_y + 182)
#define CHANGE_SKIN_6_DOWN (pic_y + 182 + chess_icon_size)
#define CHANGE_SKIN_6_LEFT (pic_x + 343)
#define CHANGE_SKIN_6_RIGHT (pic_x + 343 + chess_icon_size)
//��Ƥ���رհ�ť
#define CLOSE_UP (pic_y + 7)
#define CLOSE_DOWN (pic_y + 42)
#define CLOSE_LEFT (pic_x + 372)
#define CLOSE_RIGHT (pic_x + 441)
enum which_rival {
    HUMAN,
    AI
};
enum which_side {
    WHITE_SIDE,
    BLACK_SIDE //�ֱ��ǰ׷�����ͺڷ�����
};
enum which_page {
    GAME_PAGE,
    SKIN_PAGE,
    WIN_PAGE
};
struct point {
    int x = 0;
    int y = 0;
};
#endif // !_NEW_
