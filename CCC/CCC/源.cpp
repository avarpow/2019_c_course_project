#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
struct point {
	int x = 0;
	int y = 0;
	int vis = 0;
};
void playjj();
void m_black();
void m_white();
void p_chess0(int, int);
void p_chess1(int, int);

void withdraw_1(struct point);
void withdraw_2(struct point);

int main()
{
	IMAGE img, img1, img2, img3, img4;
	initgraph(1110, 774);
	setbkcolor(RGB(245, 211, 155));
	cleardevice();
	loadimage(&img, L"棋盘.png", 1110, 774);
	putimage(0, 0, &img);
	setcolor(BLACK);
	setfillcolor(BLACK);
	//左上角第一个交点坐标为236，115
/*	for (int i = 0; i < 15; i++) {
	fillcircle(234+46*i, 113, 22);
	}

//	fillcircle(255, 105, 20);
	for (int i = 0; i < 15; i++) {
		fillcircle(234, 113 + 46 * i, 22);
	}
	loadimage(&img1, L"jian.jpg", 60, 60);
	loadimage(&img2, L"jianjian.jpg", 60, 60);
	loadimage(&img3, L"kun.jpg", 50, 50);
	loadimage(&img4, L"kunkun.jpg", 50, 50);*/
	//_getch();
	playjj();
//	closegraph();
	return 0;
}

void m_black(){
	setlinecolor(BLACK);
	setfillcolor(BLACK);

}

void m_white(){
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}

void p_chess0(int x, int y) {
	IMAGE img1, img2;
	loadimage(&img1, L"jian.jpg", 46, 46);
	loadimage(&img2, L"jianjian.jpg", 46, 46);
	putimage(x - 23, y - 23, &img1, NOTSRCERASE);
	putimage(x - 23, y - 23, &img2, SRCINVERT);
}

void p_chess1(int x, int y) {
	IMAGE img1, img2;
	loadimage(&img1, L"kun.jpg", 46, 46);
	loadimage(&img2, L"kunkun.jpg", 46, 46);
	putimage(x - 23, y - 23, &img1, NOTSRCERASE);
	putimage(x - 23, y - 23, &img2, SRCINVERT);
}

void withdraw_1(struct point temp) {
	IMAGE img;
	loadimage(&img, L"huiqi3", 46, 46);
	putimage(temp.x - 23, temp.y - 23, &img);
}

void withdraw_2(struct point temp) {
	IMAGE img;
	loadimage(&img, L"huiqi2", 46, 46);
	putimage(temp.x - 23, temp.y - 23, &img);
}

void playjj() {
	MOUSEMSG m_mouse;
	int count = 0;
	struct point map[15][15];
	vector <struct point> camera;
	map[0][0].x = 234;
	map[0][0].y = 113;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			map[i][j].x = 234 + 46 * i;		
			map[i][j].y = 113 + 46 * j;
			map[i][j].vis = 0;
		}
	}
/*	for (int i = 0; i < 15; i++) {
		fillcircle(234 + 46 * i, 113, 22);
	}

	//	fillcircle(255, 105, 20);
	for (int i = 0; i < 15; i++) {
		fillcircle(234, 113 + 46 * i, 22);
	}
	m_white();
	fillcircle(map[13][13].x, map[13][13].y, 22);
	fillcircle(map[0][0].x, map[0][0].y, 22);*/
	while (1) {
		int j;
		m_mouse = GetMouseMsg();

		switch (m_mouse.uMsg) {	
		
		case WM_LBUTTONDOWN:
		{	int x0 = m_mouse.x, y0 = m_mouse.y;
			struct point temp;
			if(x0 >= map[0][0].x - 23 && x0 <= map[14][14].x + 23 && y0 >= map[0][0].y - 23 && y0 <= map[14][14].y + 23){
				for (int p = 0; p < 15; p++) {
					int t = 0;
					for (int q = 0; q < 15; q++) {
						if (x0 >= map[p][q].x - 23 && x0 <= map[p][q].x + 23 && y0 >= map[p][q].y - 23 && y0 <= map[p][q].y + 23) {
							x0 = map[p][q].x;
							y0 = map[p][q].y;
							map[p][q].vis++;
							temp.vis = map[p][q].vis;
						}
						t++;
					}
				}
				
				temp.x = x0;
				temp.y = y0;
				camera.push_back(temp);
				count++;
				j = count % 2;
				switch (j){
				case 0: {
					if (temp.vis >=2 ) {
						count--;
						break;
					}
				m_black();
//				fillcircle(x0, y0, 22);
				p_chess0(x0, y0);
				cout << m_mouse.x << m_mouse.y << endl;
				break;
				}
				case 1: {
					if (temp.vis >=2) {
						count--;
						break;
					}
					m_white();
//					fillcircle(x0, y0, 22);
					p_chess1(x0, y0);
					cout << m_mouse.x << m_mouse.y << endl;
					break;
				}
				}
			}
		else if (x0 >= 51 && x0 <= 144 && y0 >= 366 && y0 <= 404) {
				count--;
				temp = camera.back();
	//			fillcircle(temp.x, temp.y, 20);
				for (int i = 0; i < 15; i++) {
					for (int j = 0; j < 15; j++) {
						if (temp.x == map[i][j].x && temp.y == map[i][j].y) {
							map[i][j].vis = 0;
						}
					}
				}
				if ((temp.x == map[3][3].x && temp.y == map[3][3].y) ||( temp.x == map[3][11].x && temp.y == map[3][11].y) || (temp.x == map[11][3].x && temp.y == map[11][3].y) || (temp.x == map[11][11].x && temp.y == map[11][11].y) || (temp.x == map[7][7].x && temp.y == map[7][7].y)) {
					withdraw_1(temp);
				}
				else {
					withdraw_2(temp);
				}
				camera.pop_back();
			}
		}
	}

	}
}