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
bool in_range_set_chess(MOUSEMSG m_mouse);
bool in_range_withdraw(MOUSEMSG m_mouse);
void set_chess(MOUSEMSG m_mouse,int &play_side_now);
void withdraw();
void draw_chess_board(int chess_board[][15]);
int one_side_win(int which_side);
int is_five(int row,int column,int which_side);
void win(int which_side);
void save_game_record();
void play();
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
enum which_side{
    WHITE_SIDE,BLACK_SIDE//分别是白方下棋和黑方下棋
};
enum which_page{
    GAME_PAGE,SKIN_PAGE,WIN_PAGE
};
struct point {
	int x = 0;
	int y = 0;
};
//棋盘上黑棋为1，白棋为1-，无棋子是0
int chess_board[15][15]={0};
int play_side_now;//描述当前是白方还是黑方下棋
int white_using_skin_num;
int black_using_skin_num;
int white_money;
int black_money;
int now_page=GAME_PAGE;
IMAGE pic_chess_board,skin[6],skin_mask[6],skin_icon[6],skin_mask_icon[6];
IMAGE white_win,black_win,record_success，numbers[10];
vector <struct point> game_record;
MOUSEMSG m_mouse;

int main(){
    load_image();
    game_init();
    play();
}
void load_image(){
    loadimage(&pic_chess_board,L"qipan.jpg",1110,774);
    loadimage(&skin_mask[0],L"jian.jpg",46,46);
    loadimage(&skin[0],L"jianjian.jpg",46,46);
    loadimage(&skin_mask[1],L"kun.jpg",46,46);
    loadimage(&skin[1],L"kunkun.jpg",46,46);
    loadimage(&skin_mask[2],L"xiongmao1.jpg",46,46);
    loadimage(&skin[2],L"xiongmao.jpg",46,46);
    loadimage(&skin_mask[3],L"leishen1.jpg",46,46);
    loadimage(&skin[3],L"leishen.jpg",46,46);
    loadimage(&skin_mask[4],L"zongzi1.jpg",46,46);
    loadimage(&skin[4],L"zongzi.jpg",46,46);
    loadimage(&skin_mask[5],L"angel1.jpg",46,46);
    loadimage(&skin[5],L"angel.jpg",46,46);
    loadimage(&white_win,L"whitewin.jpg");
    loadimage(&black_win,L"blackwin.jpg");
    loadimage(&record_success,L"record_success.jpg");
}
void game_init(){
    //棋盘置零，棋局记录清空，双方使用0号皮肤，双方金钱清零
	initgraph(1110, 774);    
    memset(chess_board,0,sizeof(chess_board));
    game_record.clear();
    play_side_now=BLACK_SIDE;
    white_using_skin_num=0;
    black_using_skin_num=1;
    white_money=0;
    black_money=0;
    draw_chess_board(chess_board);
}
bool in_range_white_change_skin(MOUSEMSG m_mouse){
    //判断是否在白棋换皮肤范围之内
    if(m_mouse.x>=WHITE_CHANGE_SKIN_LEFT && m_mouse.x<=WHITE_CHANGE_SKIN_RIGHT && m_mouse.y>=WHITE_CHANGE_SKIN_UP && m_mouse.y<=WHITE_CHANGE_SKIN_DOWN){
        return true;
    }
    else return false;
}
bool in_range_black_change_skin(MOUSEMSG m_mouse){
    //判断是否在黑棋换皮肤范围之内
    if(m_mouse.x>=BLACK_CHANGE_SKIN_LEFT && m_mouse.x<=BLACK_CHANGE_SKIN_RIGHT && m_mouse.y>=BLACK_CHANGE_SKIN_UP && m_mouse.y<=BLACK_CHANGE_SKIN_DOWN){
        return true;
    }
    else return false;
}
bool in_range_set_chess(MOUSEMSG m_mouse){
    //判断是否在下棋范围之内
    if(m_mouse.x>=CHESS_LEFT && m_mouse.x<=CHESS_RIGHT && m_mouse.y>=CHESS_UP && m_mouse.y<=CHESS_DOWN){
        return true;
    }
    else return false;
}
bool in_range_return(MOUSEMSG m_mouse){
    //判断是否在返回菜单范围之内
    if(m_mouse.x>=RETURN_LEFT && m_mouse.x<=RETURN_RIGHT && m_mouse.y>=RETURN_UP && m_mouse.y<=RETURN_DOWN){
        return true;
    }
    else return false;
}
bool in_range_record_end(MOUSEMSG m_mouse){
    //判断是否在胜利界面的记录对局之内
    if(m_mouse.x>=RECORD_END_LEFT && m_mouse.x<=RECORD_END_RIGHT && m_mouse.y>=RECORD_END_UP && m_mouse.y<=RECORD_END_DOWN){
        return true;
    }
    else return false;
}
bool in_range_replay(MOUSEMSG m_mouse){
    //判断是否在精彩重播之内
    if(m_mouse.x>=REPLAY_LEFT && m_mouse.x<=REPLAY_RIGHT && m_mouse.y>=REPLAY_UP && m_mouse.y<=REPLAY_DOWN){
        return true;
    }
    else return false;
}
bool in_range_withdraw(MOUSEMSG m_mouse){
    //判断是否在悔棋按钮范围之内
    if(m_mouse.x>=WITHDRAW_LEFT && m_mouse.x<=WITHDRAW_RIGHT && m_mouse.y>=WITHDRAW_UP && m_mouse.y<=WITHDRAW_DOWN){
        return true;
    }
    else return false;
}
bool in_range_record(MOUSEMSG m_mouse){
    if(m_mouse.x>=RECORD_LEFT && m_mouse.x<=RECORD_RIGHT && m_mouse.y>=RECORD_UP && m_mouse.y<=RECORD_DOWN){
        return true;
    }
    else return false;
}
void set_chess(MOUSEMSG m_mouse,int &play_side_now){
    //根据鼠标位置和现在是哪一方在下棋来落子
    point temp;
    temp.x=max(0,(m_mouse.x-234+23)/46);
    temp.x=min(temp.x,14);
    temp.y=max(0,(m_mouse.y-113+23)/46);
    temp.y=min(temp.y,14);
    if(chess_board[temp.x][temp.y]==0){
        game_record.push_back(temp);
        switch(play_side_now){
            case WHITE_SIDE:
            {
                chess_board[temp.x][temp.y] = -1;    
                play_side_now=BLACK_SIDE;
                break;
            }
            case BLACK_SIDE:
            {
                chess_board[temp.x][temp.y]=1;
                play_side_now=WHITE_SIDE;
                break;
            }
        }
        draw_chess_board(chess_board);
    }
}
void withdraw(){
    //悔棋
    if(game_record.size()>0){
        point last_point=game_record.back();
        game_record.pop_back();
        chess_board[last_point.x][last_point.y]=0;
        draw_chess_board(chess_board);
    }
}
void wait_mouse_click(){
    int flag=1;
    while(flag){
        m_mouse = GetMouseMsg();
        switch (m_mouse.uMsg) {	
            case WM_LBUTTONDOWN:{
                flag=0;
            }
        }
    }
}
void draw_chess_board(int chess_board[][15]){
    //画棋盘，字面意思
	setbkcolor(RGB(245, 211, 155));
	cleardevice();
	putimage(0, 0, &pic_chess_board);

    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){ 
            if(chess_board[i][j]==1){
                putimage(234-23+46*i, 113-23+46*j, &skin_mask[black_using_skin_num],NOTSRCERASE);
                putimage(234-23+46*i, 113-23+46*j, &skin[black_using_skin_num],SRCINVERT);

            }
            else if(chess_board[i][j]==-1){
                putimage(234-23+46*i, 113-23+46*j, &skin_mask[white_using_skin_num],NOTSRCERASE);
                putimage(234-23+46*i, 113-23+46*j, &skin[white_using_skin_num],SRCINVERT);
            }
        }
    }
}
int is_five(int row,int column,int which_side){
    int i, j, k = 0, p[4] = {0,-1,-1,-1}, q[4] = {1,1,0,-1,},chess_count=0,z;
    if(which_side == WHITE_SIDE){
        z=-1;
    }
    else if(which_side == BLACK_SIDE){
        z=1;
    }
	for (i = 0; i < 4; i++)
	{
		for (j = -4; j <= 4 && (row + p[i] * j)<15 && (row + p[i] * j)>=0 && (column + q[i] * j)<15 && (column + q[i] * j)>=0; j++)
		{
			if (chess_board[row + p[i]*j][column + q[i]*j] != z)chess_count=0;
			else chess_count++;
			if (chess_count == 5)k = 1;
		}
	}
	return k;
    }
int is_one_side_win(int which_side){
    if(which_side == WHITE_SIDE){
        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++){
                if(is_five(i,j,WHITE_SIDE)){
                    return 1;
                }
            }
        }
    }
    if(which_side == BLACK_SIDE){
        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++){
                if(is_five(i,j,BLACK_SIDE)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

void game_reset(){
    memset(chess_board,0,sizeof(chess_board));
    game_record.clear();
    play_side_now=BLACK_SIDE;
    draw_chess_board(chess_board);
}
void game_replay(){
    memset(chess_board,0,sizeof(chess_board));
    play_side_now=BLACK_SIDE;
    for(int i=0;i<game_record.size();i++){
        
        switch(play_side_now){
            case WHITE_SIDE:
            {
                chess_board[game_record[i].x][game_record[i].y] = -1;    
                play_side_now=BLACK_SIDE;
                break;
            }
            case BLACK_SIDE:
            {
                chess_board[game_record[i].x][game_record[i].y]=1;
                play_side_now=WHITE_SIDE;
                break;
            }
        }
        draw_chess_board(chess_board);
        Sleep(500);
    }
    wait_mouse_click();
    if(is_one_side_win(WHITE_SIDE)){
        win(WHITE_SIDE);
    }
    else if(is_one_side_win(BLACK_SIDE)){
        win(BLACK_SIDE);
    }
}
void after_win_action(){
    now_page=WIN_PAGE;
    int flag=1;
    while(flag){
        m_mouse = GetMouseMsg();
        switch (m_mouse.uMsg) {	
            case WM_LBUTTONDOWN:{
                if(in_range_return(m_mouse)){
                    flag=0;
                }
                else if(in_range_record_end(m_mouse)){
                    save_game_record();
                        }
                else if(in_range_replay(m_mouse)){
                    flag=0;
                    game_replay();
                }
            }
        }
    }
}
void win(int which_side){
    if(which_side== WHITE_SIDE){
        white_money+=10;
        putimage(0, 0, &white_win);
        after_win_action();
		game_reset();
    }
    else if(which_side == BLACK_SIDE){
        black_money+=10;
        putimage(0, 0, &black_win);
        after_win_action();
        game_reset();
    }

}
void save_game_record(){
    FILE *fp=fopen("game_record.txt","w");
	if(fp==NULL)printf("open file failed£¡\n");
    else {
        int i=1;
        for(auto iter=game_record.begin();iter != game_record.end();++iter){
            fprintf(fp,"step:%d row=%d column=%d\n",i++,(*iter).x,(*iter).y);
        }
    }
    fclose(fp);
    putimage(500, 350, &record_success);
    wait_mouse_click();
    if(now_page== GAME_PAGE){
    draw_chess_board(chess_board);
    }
    else if(now_page == WIN_PAGE){
        if(is_one_side_win(WHITE_SIDE)){
            putimage(0, 0, &white_win);
        }
        else if(is_one_side_win(BLACK_SIDE)){
            putimage(0, 0, &black_win);
        }
    }
}
void play(){
    while(1){
        m_mouse = GetMouseMsg();
        switch (m_mouse.uMsg) {	
            case WM_LBUTTONDOWN:{
                if(in_range_set_chess(m_mouse)){
                    set_chess(m_mouse,play_side_now);
                    if(is_one_side_win(WHITE_SIDE)){
                        win(WHITE_SIDE);
                    }
                    else if(is_one_side_win(BLACK_SIDE)){
                        win(BLACK_SIDE);
                    }
                }
                else if(in_range_withdraw(m_mouse)){
                    withdraw();
                }
                else if(in_range_record(m_mouse)){
                    save_game_record();
                }
                //这里以后加更多按钮的功能
            }
        }
    }
}
