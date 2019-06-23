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
int chess_size=46;
int chess_icon_size=120;
int pic_x=300,pic_y=200;
IMAGE pic_chess_board,pic_skin_change,skin[6],skin_mask[6],skin_icon[6],skin_mask_icon[6];
IMAGE white_win,black_win,record_success,numbers[10];
vector <struct point> game_record;
MOUSEMSG m_mouse;

int main(){
    load_image();
    game_init();
    play();
}
void load_image(){
    loadimage(&pic_chess_board,L"qipan.jpg",1110,774);
    loadimage(&pic_skin_change,L"pifuxuanze.jpg");
    loadimage(&skin_mask[0],L"jian.jpg",chess_size,chess_size);
    loadimage(&skin[0],L"jianjian.jpg",chess_size,chess_size);
    loadimage(&skin_mask[1],L"kun.jpg",chess_size,chess_size);
    loadimage(&skin[1],L"kunkun.jpg",chess_size,chess_size);
    loadimage(&skin_mask[2],L"xiongmao1.jpg",chess_size,chess_size);
    loadimage(&skin[2],L"xiongmao.jpg",chess_size,chess_size);
    loadimage(&skin_mask[3],L"leishen1.jpg",chess_size,chess_size);
    loadimage(&skin[3],L"leishen.jpg",chess_size,chess_size);
    loadimage(&skin_mask[4],L"zongzi1.jpg",chess_size,chess_size);
    loadimage(&skin[4],L"zongzi.jpg",chess_size,chess_size);
    loadimage(&skin_mask[5],L"angel1.jpg",chess_size,chess_size);
    loadimage(&skin[5],L"angel.jpg",chess_size,chess_size);
    loadimage(&skin_mask_icon[0],L"jian.jpg",chess_icon_size,chess_icon_size);
    loadimage(&skin_icon[0],L"jianjian.jpg",chess_icon_size,chess_icon_size);
    loadimage(&skin_mask_icon[1],L"kun.jpg",chess_icon_size,chess_icon_size);
    loadimage(&skin_icon[1],L"kunkun.jpg",chess_icon_size,chess_icon_size);
    loadimage(&skin_mask_icon[2],L"xiongmao1.jpg",chess_icon_size,chess_icon_size);
    loadimage(&skin_icon[2],L"xiongmao.jpg",chess_icon_size,chess_icon_size);
    loadimage(&skin_mask_icon[3],L"leishen1.jpg",chess_icon_size,chess_icon_size);
    loadimage(&skin_icon[3],L"leishen.jpg",chess_icon_size,chess_icon_size);
    loadimage(&skin_mask_icon[4],L"zongzi1.jpg",chess_icon_size,chess_icon_size);
    loadimage(&skin_icon[4],L"zongzi.jpg",chess_icon_size,chess_icon_size);
    loadimage(&skin_mask_icon[5],L"angel1.jpg",chess_icon_size,chess_icon_size);
    loadimage(&skin_icon[5],L"angel.jpg",chess_icon_size,chess_icon_size);
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

bool in_range_change_skin_1(MOUSEMSG m_mouse){
    //判断是否在皮肤1范围之内
    if(m_mouse.x>=CHANGE_SKIN_1_LEFT && m_mouse.x<=CHANGE_SKIN_1_RIGHT && m_mouse.y>=CHANGE_SKIN_1_UP && m_mouse.y<=CHANGE_SKIN_1_DOWN){
        return true;
    }
    else return false;
}bool in_range_change_skin_2(MOUSEMSG m_mouse){
    //判断是否在皮肤2范围之内
    if(m_mouse.x>=CHANGE_SKIN_2_LEFT && m_mouse.x<=CHANGE_SKIN_2_RIGHT && m_mouse.y>=CHANGE_SKIN_2_UP && m_mouse.y<=CHANGE_SKIN_2_DOWN){
        return true;
    }
    else return false;
}bool in_range_change_skin_3(MOUSEMSG m_mouse){
    //判断是否在皮肤3范围之内
    if(m_mouse.x>=CHANGE_SKIN_3_LEFT && m_mouse.x<=CHANGE_SKIN_3_RIGHT && m_mouse.y>=CHANGE_SKIN_3_UP && m_mouse.y<=CHANGE_SKIN_3_DOWN){
        return true;
    }
    else return false;
}bool in_range_change_skin_4(MOUSEMSG m_mouse){
    //判断是否在皮肤4范围之内
    if(m_mouse.x>=CHANGE_SKIN_4_LEFT && m_mouse.x<=CHANGE_SKIN_4_RIGHT && m_mouse.y>=CHANGE_SKIN_4_UP && m_mouse.y<=CHANGE_SKIN_4_DOWN){
        return true;
    }
    else return false;
}bool in_range_change_skin_5(MOUSEMSG m_mouse){
    //判断是否在皮肤5范围之内
    if(m_mouse.x>=CHANGE_SKIN_5_LEFT && m_mouse.x<=CHANGE_SKIN_5_RIGHT && m_mouse.y>=CHANGE_SKIN_5_UP && m_mouse.y<=CHANGE_SKIN_5_DOWN){
        return true;
    }
    else return false;
}bool in_range_change_skin_6(MOUSEMSG m_mouse){
    //判断是否在皮肤6范围之内
    if(m_mouse.x>=CHANGE_SKIN_6_LEFT && m_mouse.x<=CHANGE_SKIN_6_RIGHT && m_mouse.y>=CHANGE_SKIN_6_UP && m_mouse.y<=CHANGE_SKIN_6_DOWN){
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
void show_skin(){
    putimage(pic_x,pic_y,&pic_skin_change);
    putimage(pic_x+38,pic_y+47,&skin_mask_icon[0],NOTSRCERASE);
    putimage(pic_x+38,pic_y+47,&skin_icon[0],SRCINVERT);
    putimage(pic_x+189,pic_y+47,&skin_mask_icon[1],NOTSRCERASE);
    putimage(pic_x+189,pic_y+47,&skin_icon[1],SRCINVERT);
    putimage(pic_x+337,pic_y+47,&skin_mask_icon[2],NOTSRCERASE);
    putimage(pic_x+337,pic_y+47,&skin_icon[2],SRCINVERT);
    putimage(pic_x+38,pic_y+182,&skin_mask_icon[3],NOTSRCERASE);
    putimage(pic_x+38,pic_y+182,&skin_icon[3],SRCINVERT);
    putimage(pic_x+187,pic_y+182,&skin_mask_icon[4],NOTSRCERASE);
    putimage(pic_x+187,pic_y+182,&skin_icon[4],SRCINVERT);
    putimage(pic_x+343,pic_y+182,&skin_mask_icon[5],NOTSRCERASE);
    putimage(pic_x+343,pic_y+182,&skin_icon[5],SRCINVERT);
}
int chose_skin(){
    //不知道为什么要点很多次才有作用
    int flag=1,k=0;
    while(flag){
        m_mouse = GetMouseMsg();
        switch (m_mouse.uMsg) {	
            case WM_LBUTTONDOWN:{
                if(in_range_change_skin_1(m_mouse)){
                    k=0;
                    flag=0;
                }
                else if(in_range_change_skin_2(m_mouse)){
                    k=1;
                    flag=0;
                }
                else if(in_range_change_skin_3(m_mouse)){
                    k=2;
                    flag=0;
                }
                else if(in_range_change_skin_4(m_mouse)){
                    k=3;
                    flag=0;                
                }
                else if(in_range_change_skin_5(m_mouse)){
                    k=4;
                    flag=0;
                }
                else if(in_range_change_skin_6(m_mouse)){
                    k=5;
                    flag=0;
                }
            }
        }
    }
    return k;
}
void white_skin_change(){
    show_skin();
    int new_skin=chose_skin();
    if(new_skin!=black_using_skin_num){
         white_using_skin_num=new_skin;
    }
}
void black_skin_change(){
    show_skin();
    int new_skin=chose_skin();
    if(new_skin!=white_using_skin_num){
        black_using_skin_num=new_skin;
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
                else if(in_range_white_change_skin(m_mouse)){
                    white_skin_change();
                }
                else if(in_range_black_change_skin(m_mouse)){
                    black_skin_change();
                }
                //这里以后加更多按钮的功能
            }
        }
    }
}
