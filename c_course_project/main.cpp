#include<graphics.h>
#include<conio.h>
int main()
{
	int step = 30;
	initgraph(600, 600);
	setbkcolor(RGB(245,211,155));
		cleardevice();
	setlinestyle(PS_SOLID, 1);

		setcolor(RGB(0, 0, 0));
		int i;
		for (i = 1; i <= 19; i++) {
			line(i* step, 1 * step, i* step, 19 * step);
			line(1 * step, i* step, 19 * step, i*step);
		}
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(120, 120, 15);
		setcolor(WHITE);
		setfillcolor(WHITE);
		fillcircle(120, 90, 15);
	_getch();
	closegraph();
	return 0;
}