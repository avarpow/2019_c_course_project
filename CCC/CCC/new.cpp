#include<graphics.h>
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
void play();
//棋盘范围
#define CHESS_UP 207
#define CHESS_DOWN 906
#define CHESS_LEFT 98
#define CHESS_RIGHT 772
//悔棋按钮范围
#define WITHDRAW_UP 51
#define WITHDRAW_DOWN 144
#define WITHDRAW_LEFT 366
#define WITHDRAW_RIGHT 404
enum which_side{
    WHITE_SIDE,BLACK_SIDE//分别是白方下棋和黑方下棋
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
IMAGE pic_chess_board,white_skin[2],white_skin_mask[2],black_skin[2],black_skin_mask[2];
IMAGE white_win,white_win_mask,black_win,black_win_mask;
vector <struct point> game_record;
MOUSEMSG m_mouse;

int main(){
    load_image();
    game_init();
    play();
}
void load_image(){
    loadimage(&pic_chess_board,L"qipan.png",1110,774);
    loadimage(&white_skin_mask[0],L"jian.jpg",46,46);
    loadimage(&white_skin[0],L"jianjian.jpg",46,46);
    loadimage(&black_skin_mask[0],L"kun.jpg",46,46);
    loadimage(&black_skin[0],L"kunkun.jpg",46,46);
    loadimage(&white_win_mask,L"jian.jpg",46,46);
    loadimage(&white_win,L"jianjian.jpg",46,46);
    loadimage(&black_win_mask,L"kun.jpg",46,46);
    loadimage(&black_win,L"kunkun.jpg",46,46);
}
void game_init(){
    //棋盘置零，棋局记录清空，双方使用0号皮肤，双方金钱清零
    initgraph(1110, 774);
    memset(chess_board,0,sizeof(chess_board));
    game_record.clear();
    play_side_now=BLACK_SIDE;
    white_using_skin_num=0;
    black_using_skin_num=0;
    white_money=0;
    black_money=0;
    draw_chess_board(chess_board);
}
bool in_range_set_chess(MOUSEMSG m_mouse){
    //判断是否在下棋范围之内
    if(m_mouse.x>=CHESS_UP && m_mouse.x<=CHESS_DOWN && m_mouse.y>=CHESS_LEFT && m_mouse.y<=CHESS_RIGHT){
        return true;
    }
    else return false;
}
bool in_range_withdraw(MOUSEMSG m_mouse){
    //判断是否在悔棋按钮范围之内
    if(m_mouse.x>=WITHDRAW_UP && m_mouse.x<=WITHDRAW_DOWN && m_mouse.y>=WITHDRAW_LEFT && m_mouse.y<=WITHDRAW_RIGHT){
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

void draw_chess_board(int chess_board[][15]){
    //画棋盘，字面意思
	setbkcolor(RGB(245, 211, 155));
	cleardevice();
	putimage(0, 0, &pic_chess_board);
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){ 
            if(chess_board[i][j]==1){
                putimage(234-23+46*i, 113-23+46*j, &black_skin_mask[black_using_skin_num],NOTSRCERASE);
                putimage(234-23+46*i, 113-23+46*j, &black_skin[black_using_skin_num],SRCINVERT);

            }
            else if(chess_board[i][j]==-1){
                putimage(234-23+46*i, 113-23+46*j, &white_skin_mask[white_using_skin_num],NOTSRCERASE);
                putimage(234-23+46*i, 113-23+46*j, &white_skin[white_using_skin_num],SRCINVERT);
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
int one_side_win(int which_side){
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
    white_using_skin_num=0;
    black_using_skin_num=0;
    draw_chess_board(chess_board);
}
void win(int which_side){
    if(which_side== WHITE_SIDE){
        white_money+=10;
        putimage(white_money, white_money, &white_win_mask,NOTSRCERASE);
        putimage(white_money, white_money, &white_win,SRCINVERT);
        //这里要加入胜利后的画面和按钮
		game_reset();
    }
    else if(which_side == BLACK_SIDE){
        black_money+=10;
        putimage(black_money, black_money, &black_win_mask,NOTSRCERASE);
        putimage(black_money, black_money, &black_win,SRCINVERT);
        //这里要加入胜利后的画面和按钮
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
}
void play(){
    while(1){
        m_mouse = GetMouseMsg();
        switch (m_mouse.uMsg) {	
            case WM_LBUTTONDOWN:{
                if(in_range_set_chess(m_mouse)){
                    set_chess(m_mouse,play_side_now);
                    if(one_side_win(WHITE_SIDE)){
                        win(WHITE_SIDE);
                    }
                    else if(one_side_win(BLACK_SIDE)){
                        win(BLACK_SIDE);
                    }
                }
                else if(in_range_withdraw(m_mouse)){
                    //withdraw();
                    save_game_record();
                }
                //这里以后加更多按钮的功能
            }
        }
    }
}
