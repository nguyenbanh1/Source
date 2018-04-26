#include <iostream>
#include <conio.h>
#include "graphics.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include<fstream>
#include<time.h>
#include<math.h>
using namespace std;

enum TrangThai { UP, DOWN, LEFT, RIGHT, DEAD, ALIVE, CONG, STOP }; // Đặt dấu hiệu (cờ)
struct point {
	int x;
	int y;
};
struct SNAKE {
	point dot[20];
	int n; // độ dài của con rắn
};
int a, b; // tọa độ ban đầu của con rắn
int Score ;
int food_ ;
int level;
int speed ;
char ch;
int x_1, y_1;
int flag;
fstream filegame;
TrangThai tt, tt1, tt2, tt3;
SNAKE snake;
point food;
char *tenfile; // như kiểu như tên đăng nhập
char MSSV[] = { '1','6','6','0','3','8','4' };
int flag1;//kiem tra file moi vo tao chua , neu tao thi flag1 = 0 và ngược lại
int flag10 =-1;//để kiểm tra trong quá trình tạo bản
void khoitaoWindow()// khởi tạo cửa sổ windown và màn hình
{
	int gd = DETECT, gm, errorcode; //yeu cau auto-detection.
									//khoi tao cac bien do hoa va cuc bo.
	initgraph(&gd, &gm, "C://Users//hp//Desktop//BGI2010"); //la path cai dat graphics drivers
															//doc ket qua cua trình khoi tao.
	errorcode = graphresult();
	//neu co mot loi xay ra.
	if (errorcode != grOk)
	{
		cout << "Xuat hien mot loi: \n" << grapherrormsg(errorcode) << endl;
		cout << "Nhan bat ky phim nao de dung lai : ";

		exit(1);
	}
	initwindow(1200, 600);

}
// tạo file
void Initiazation() // khởi tạo các giá trị : các đốt con rắn , chiều dài con rắn
{
	snake.n = 7; // chiều dài con rắn
	snake.dot[0].x = 100;
	snake.dot[0].y = 109;
	snake.dot[1].x = 100;
	snake.dot[1].y = 118;
	snake.dot[2].x = 100;
	snake.dot[2].y = 127;
	snake.dot[3].x = 100;
	snake.dot[3].y = 136;
	snake.dot[4].x = 100;
	snake.dot[4].y = 145;
	snake.dot[5].x = 100;
	snake.dot[5].y = 154;
	snake.dot[6].x = 100;
	snake.dot[6].y = 163;
	speed = 1;
	level = 1;
	food_ = 0;
	Score = 0;
	a = 100;
	b = 109;
}
void DrawFood();
void DrawSnake();
void banglon();
void pause();
//khởi tạo lại ban đầu
void ResetData()
{
	
	DrawFood();
	DrawSnake();
	while (true)
	{
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_UP))
		{
			tt = ALIVE;
			a = snake.dot[0].x;
			b = snake.dot[0].y;
			break;
		}
	}
}
//tạo GAMELODING...
void Output3();
void Output1()
{
	settextstyle(DEFAULT_FONT, LEFT_TEXT, 4);
	settextjustify(CENTER_TEXT, VCENTER_TEXT);
	char  * ch = (char *)malloc(100);
	for (int i = 0; i <= 100; i++)
	{
		delay(10);
		sprintf(ch, "GAME LOADING %d ", i);
		outtextxy(600, 300, ch);
		moveto(860, 300);
		outtext("%");
	}
	delay(500);
	cleardevice();
	delete[]ch;
}
void Output()
{
	settextstyle(DEFAULT_FONT, LEFT_TEXT, 7);
	settextjustify(CENTER_TEXT, VCENTER_TEXT);
	setcolor(GREEN);
	outtextxy(600, 150,"GAME SNAKE");
	settextstyle(DEFAULT_FONT, LEFT_TEXT, 3);
	settextjustify(CENTER_TEXT, VCENTER_TEXT);
	outtextxy(600, 300, "TANG KHANH NGUYEN");
	outtextxy(600, 350, "MSSV : 1660384");
	outtextxy(600, 400, "LOP: 16CK2");
	getch();
	cleardevice();
}
void Output2() // makefile
{
	setcolor(YELLOW);
	settextstyle(DEFAULT_FONT, LEFT_TEXT, 2);
	settextjustify(CENTER_TEXT, VCENTER_TEXT);
	outtextxy(600, 300, "NHAP TEN :");
	tenfile = new char[30];
	int i = 0;
	while (true)
	{
		if (kbhit())
		{
			char ch = getch();
			if (ch != 13)
			{
				tenfile[i] = ch;
				tenfile[i + 1] = '\0';
				//cout << tenfile;
				outtextxy(600, 320, tenfile);
				i++;
			}
			else break;
		}
	}
	filegame.open(tenfile, ios_base::in);
	if (filegame)
	{
		//flag1 = 0;
		filegame >> Score;
		filegame >> food_;
		filegame >> level;
		filegame >> speed;
		filegame >> snake.n;
		filegame >> food.x;
		filegame >> food.y;
		for (int i = 0; i < snake.n; i++)
		{
			filegame >> snake.dot[i].x;
			filegame >> snake.dot[i].y;
		}
	}
	else
	{
		Initiazation();
		filegame.open(tenfile, ios_base::out);
		filegame << Score << endl;
		filegame << food_ << endl;
		filegame << level << endl;
		filegame << speed << endl;
		filegame << snake.n << endl;
		filegame << food.x << endl;
		filegame << food.y << endl;
		for (int i = 0; i < snake.n; i++)
		{
			filegame << snake.dot[i].x << endl;
			filegame << snake.dot[i].y << endl;
		}
		//flag1 = 1;
	}
	filegame.close(); // kết thúc file tạo ra
}
//đánh dấu start
void bang()
{
	setcolor(RED);
	rectangle(515, 230, 680, 260); // start
	setcolor(BLACK);
	rectangle(440, 270, 780, 310); // choose level
	rectangle(515, 320, 675, 360); // about
	rectangle(515, 380, 680, 410); // quit
}
// đánh dấu choose level
void bang1()
{
	setcolor(RED);
	rectangle(440, 270, 780, 310); // choose level
	setcolor(BLACK);
	rectangle(515, 230, 680, 260); // start
	rectangle(515, 320, 675, 360); // about
	rectangle(515, 380, 680, 410); // quit
}
//đánh dấu about
void bang2()
{
	setcolor(RED);
	rectangle(515, 320, 675, 360); // about
	setcolor(BLACK);
	rectangle(440, 270, 780, 310); // choose level
	rectangle(515, 230, 680, 260); // start
	rectangle(515, 380, 680, 410); // quit
}
//đánh dấu quit
void bang3()
{
	setcolor(RED);
	rectangle(515, 380, 680, 410); // quit
	setcolor(BLACK);
	rectangle(515, 320, 675, 360); // about
	rectangle(440, 270, 780, 310); // choose level
	rectangle(515, 230, 680, 260); // start
}
// lựa chọn : START,QUIT...
void chooselevel()
{
	cleardevice();
	setcolor(YELLOW);
	settextjustify(CENTER_TEXT, VCENTER_TEXT);
	settextstyle(1, LEFT_TEXT, 4);
	outtextxy(600, 150, "CHOOSE LEVEL");
	settextstyle(1, LEFT_TEXT, 3);
	outtextxy(600, 250, "LEVEL 1");
	outtextxy(600, 300, "LEVEL 2");
	outtextxy(600, 350, "LEVEL 3");
	outtextxy(600, 400, "BACK");
	int y = 20;
	char ch;
	bang();
	while (true)
	{
		if (kbhit())
		{
			ch = getch();
			if (ch == 72)
			{
				y--;
				if (y == 19) y = 23;
			}
			else if (ch == 80)
			{
				y++;
				if (y == 24) y = 20;
			}
		}

		switch (y)
		{
		case 20:
			bang();
			if (getch() == 13)
			{
				cleardevice();
				Initiazation();
				return;
			}
			break;
		case 21:
			bang1();
			if (getch() == 13)
			{
				cleardevice();
				//ResetData();
				Initiazation();
				level = 2;
				speed = 2;
				return;
			}
			break;
		case 22:
			bang2();
			if (getch() == 13)
			{
				cleardevice();
				//ResetData();
				Initiazation();
				level = 3;
				speed = 3;
				return;
			}

			break;
		case 23:
			bang3();
			if (getch() == 13)
			{
				Output3();
				return;
			}
			break;
		}
	}
}
void about()
{
	cleardevice();
	setcolor(YELLOW);
	settextjustify(LEFT_TEXT, LEFT_TEXT);
	settextstyle(1, LEFT_TEXT, 1);
	outtextxy(50, 50, "- An 4 thuc an thi tang level mot lan.");
	outtextxy(50, 70, "- Khi va cham tuong,than thi chet.");
	outtextxy(50, 90, "SAVE FILe");
	outtextxy(50, 110, "Chu y: Bam B hoac b de thoat ra lai");
	nguyen:
	if (getch() == 'B' || getch() == 'b')
	{
		Output3();
		return;
	}
	else goto nguyen;
}

void Output3()
{
	cleardevice();
	setcolor(YELLOW);
	settextjustify(CENTER_TEXT, VCENTER_TEXT);
	settextstyle(1, LEFT_TEXT, 4);
	outtextxy(600, 150, "GAME MENU");
	settextstyle(1, LEFT_TEXT, 3);
	outtextxy(600, 250, "ABOUT");
	outtextxy(600, 300, "CHOOSE LEVEL");
	outtextxy(600, 350, "START");
	outtextxy(600, 400, "QUIT");

	int y = 20;
	char ch;
	bang();
	
	while (true)
	{
		if (kbhit())
		{
			ch = getch();
		
			if (ch == 72)
			{
				y--;
				if (y == 19) y = 23;
			}
			else if (ch == 80)
			{
				y++;
				if (y == 24) y = 20;
			}
		}

		switch (y)
		{
		case 20:
			bang();
			if (getch() == 13)
			{
				about();
				//return;
			}
			break;
		case 21:
			bang1();
			if (getch() == 13)
			{
				chooselevel();
				return;
			}
			break;
		case 22:
			bang2();
			if (getch() == 13)
			{
				//clearviewport();
				return;
			}

			break;
		case 23:
			bang3();
			if (getch() == 13)
			{
				closegraph();
				exit(0);
			}
			break;
		}
	}
}
void dohoa1()
{
	khoitaoWindow();
	Output();
	Output1();
	Output2();
	Output3();
}


void banglon()
{
	setcolor(RED);

	rectangle(50, 50, 750, 350);
	setfillstyle(1, GREEN);
	floodfill(100, 100, RED);

	rectangle(59, 59, 741, 341);
	setfillstyle(1, LIGHTRED);
	floodfill(57, 57, RED);




	rectangle(800, 50, 1000, 350);
	rectangle(809, 59, 991, 341);
	floodfill(805, 55, RED);

	setcolor(YELLOW);
	settextjustify(CENTER_TEXT, VCENTER_TEXT);
	settextstyle(1, LEFT_TEXT, 1);
	outtextxy(865, 80, "SCORE:");
	outtextxy(865, 100, "FOOD:");
	outtextxy(865, 120, "LEVEL:");
	outtextxy(865, 140, "SPEED:");
	char *ch = new char[5];
	sprintf(ch, "%d", Score);
	outtextxy(930, 80, ch);
	sprintf(ch, "%d", food_);
	outtextxy(930, 100,ch);
	sprintf(ch, "%d", level);
	outtextxy(930, 120,ch);
	sprintf(ch, "%d", speed);
	outtextxy(930, 140,ch);

	setcolor(YELLOW);
	settextjustify(LEFT_TEXT, LEFT_TEXT);
	settextstyle(1, LEFT_TEXT, 1);
	outtextxy(60, 450, " --> : RIGHT");
	outtextxy(450, 450, "SPACE :PAUSE/SAVE");
	outtextxy(60, 480, " <-- : LEFT");
	int a[] = { 62,508,70,495,78,508 };
	drawpoly(3, a);
	int a1[] = { 70,495,70,515 };
	drawpoly(2, a1);
	outtextxy(80, 510, "    :UP");


	int a2[] = { 70,520,70,540 };
	int a3[] = { 62,527,70,540,78,527 };
	drawpoly(2, a2);
	drawpoly(3, a3);
	outtextxy(80, 540, "    :DOWN");
}

void DrawSnake()
{
	setcolor(RED);
	circle(snake.dot[0].x, snake.dot[0].y, 5);
	setfillstyle(1,BROWN);
	floodfill(snake.dot[0].x, snake.dot[0].y, RED);
	for (int i = 1; i < snake.n; i++)
	{
		setcolor(RED);
		circle(snake.dot[i].x,snake.dot[i].y, 5);
		setfillstyle(1, RED);
		floodfill(snake.dot[i].x, snake.dot[i].y, RED);
	}
}
void insert1(int x1, int y1)
{
	//if (food.x == x1 && food.y == y1) return;
	for (int i = snake.n; i > 0; i--)
	{
		snake.dot[i].x = snake.dot[i - 1].x;
		snake.dot[i].y = snake.dot[i - 1].y;

	}
	snake.dot[0].x = x1;
	snake.dot[0].y = y1;
}

void Move(int &x, int &y) // tọa độ của đầu con rắn
{
	if (GetAsyncKeyState(VK_LEFT) && tt != CONG)
	{
		pause();
		tt = LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && tt != CONG)
	{
		pause();
		tt = RIGHT;

	}
	else if (GetAsyncKeyState(VK_UP) && tt != CONG)
	{
		pause();
		tt = UP;
	}
	else if (GetAsyncKeyState(VK_DOWN) && tt != CONG) {
		pause();
		tt = DOWN;
	}
	switch (tt)
	{
	case LEFT:
		x-=9;
		pause();
		break;
	case RIGHT:

		x+=9;
		pause();
		break;
	case UP:

		y-=9;
		pause();
		break;
	case DOWN:

		y+=9;
		pause();
		break;
	}
	if (tt == RIGHT || tt == LEFT || tt == UP || tt == DOWN) // rắn chưa chết
	{
		tt1 = tt;
		insert1(x, y);
	}
}
void DeleteSnake()
{
	for (int i = 0; i < snake.n; i++)
	{
		moveto(snake.dot[i].x, snake.dot[i].y);
		setcolor(GREEN);
		circle(snake.dot[i].x, snake.dot[i].y, 5);
		setfillstyle(1, GREEN);
		floodfill(snake.dot[i].x, snake.dot[i].y, GREEN);
	}
}
int xacdinhtoadoa(int x, int y, int x1, int y1)
{

	float d = pow(float(x1 - x), 2) + pow(float(y1 - y), 2);
	d = sqrt(d);
	if (d <= 6)
	{
		return 1;
	}
	return 0;
}
int xacdinhtoadoa1(int x, int y, int x1, int y1)
{

	float d = pow(float(x1 - x), 2) + pow(float(y1 - y), 2);
	d = sqrt(d);
	if (d >= 6 && d <= 10)
	{
		return 2;
	}
	return 0;
}
int Xuly_VaCham()
{
	for (int i = 1; i < snake.n; i++)
	{
		if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y && tt != DEAD)  // rắn tự cắn mình (ngu)
		{
			tt = DEAD;
			return 1;
			//hieuung(snake.dot[0].x, snake.dot[0].y);
			//Sleep(100);
			//if (Hienthi() == 1) return 1;
		}
	}

	if (snake.dot[0].x <= 69 || snake.dot[0].x >= 741 || snake.dot[0].y <= 69 || snake.dot[0].y >= 331)
	{
		tt = DEAD;
		return 1;
		//hieuung(snake.dot[0].x, snake.dot[0].y);
		//Sleep(100);
		//if (Hienthi() == 1)return 1;
	} // tự tập đàu vào tường (ngu quá!!)
}
void DrawFood()
{
	int x1, y1, flag;
	while (true)
	{
		srand(time(NULL));
		x1 = 69 + rand() % (732-69+1); // [62;885]
		y1 = 69 + rand() % (331-69+1); // [62;385]
		for (int i = 0; i < snake.n; i++)
		{
			flag = 1;
			if (x1 == snake.dot[i].x && y1 == snake.dot[i].y && x1 == x_1 && y1 == y_1)
			{
				flag = 0; break;
			}
		}
		if (flag == 1)
		{
			food.x = x1;
			food.y = y1;
			setcolor(4);
			circle(x1, y1, 5);
			setfillstyle(1,4);
			floodfill(x1, y1,4);
			return;
		}

	}
}
void insert(int x1, int y1)
{
	snake.n++;
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.dot[i].x = snake.dot[i - 1].x;
		snake.dot[i].y = snake.dot[i - 1].y;
	}
	snake.dot[0].x = x1;
	snake.dot[0].y = y1;
}
void DeleteFood(int x, int y)
{
	moveto(x,y);
	setcolor(GREEN);
	circle(x,y,5);
	setfillstyle(1, GREEN);
	floodfill(x,y, GREEN);
}
void drawfood(int x, int y)
{
	moveto(x, y);
	setcolor(RED);
	circle(x, y, 5);
	setfillstyle(1, RED);
	floodfill(x, y, RED);
}
void Lo_den(int x1,int y1)
{
	//srand(time(NULL));
	//x_1 = 2 + rand() % 73; // [2;74]
	//y_1 = 2 + rand() % 23; // [2;24]
	int  flag1;
	while (true)
	{
		srand(time(NULL));
		x_1 = 69 + rand() % (732 - 69 + 1); // [62;885]
		y_1 = 69 + rand() % (331 - 69 + 1); // [62;385]
		for (int i = 0; i < snake.n; i++)
		{
			flag1 = 1;
			if ((x_1 == snake.dot[i].x && y_1 == snake.dot[i].y) && (x_1 == food.x && y_1 == food.y))
			{
				flag = 0; break;
			}
		}
		if (flag1 == 1)
		{
			setcolor(BLACK);
			circle(x_1,y_1,10);
			setfillstyle(1, BLACK);
			floodfill(x_1, y_1, BLACK);
			return;
		}

	}

}
void Hieu_Ung()
{
	tt = DEAD;
	snake.n--;
}

void Xoa_Loden(int x1, int y1)
{
	setcolor(RED);
	//circle(x_1, y_1, 10);
	setfillstyle(1, GREEN);
	floodfill(x_1, y_1, RED);
}
void Ve_loden(int x1,int y1)
{
	setcolor(BLACK);
	circle(x_1, y_1, 10);
	setfillstyle(1, BLACK);
	floodfill(x_1, y_1, BLACK);
}

int Hienthi_1(char* a)
{
	setcolor(BLUE);
	rectangle(250, 150, 600, 230);
	setfillstyle(1, BLUE);
	floodfill(260, 170, BLUE);

	settextjustify(VCENTER_TEXT, VCENTER_TEXT);
	settextstyle(1, LEFT_TEXT, 1);
	
	setcolor(YELLOW);
	outtextxy(425, 175, "CHOOSE");
	outtextxy(335, 220, "RESET");

	setcolor(WHITE);
	outtextxy(525, 220, a); // a đây có thể là continue hay save;
	while (true)
	{
		ch = getch();
		switch (ch)
		{
		case 13:return 1;
		case 75:
		nguyen:
			setcolor(WHITE);
			outtextxy(525, 220, a);

			setcolor(YELLOW);
			outtextxy(335, 220, "RESET");
			switch (getch())
			{
			case 13:
				return 1;
			case 77:
				goto nguyen1;
				break;
			}
			break;
		case 77:
		nguyen1:
			setcolor(WHITE);
			outtextxy(335, 220, "RESET");
			setcolor(YELLOW);
			outtextxy(525, 220, a);
			switch (getch())
			{
			case 13:
				return 0;
			case 75:
			 goto nguyen;
			}
		}
	}
}

void pause()
{
	if (kbhit())
	{
		ch = getch();
		if (ch == 32 && (tt == RIGHT || tt == LEFT || tt == UP || tt == DOWN))
		{
			
			tt = DEAD;
			flag10 = 1;
			
		}
		else if (ch == 27) exit(0);
		else if (ch == 'l' || ch == 'L')
		{
			
			tt = DEAD;
			flag10 = 0;
		}
	}
}
int bangxuly()
{
	setcolor(BLUE);
	rectangle(150, 150, 700, 230);
	setfillstyle(1, BLUE);
	floodfill(260, 170, BLUE);

	setcolor(YELLOW);
	settextjustify(VCENTER_TEXT, VCENTER_TEXT);
	settextstyle(1, LEFT_TEXT, 1);
	outtextxy(425, 175, "DO YOU WANT TO PLAY GAME?");
	outtextxy(335, 220, "YES");
	////char *kitu = new char[10];
	////sprintf(kitu, "%s", a);
	setcolor(WHITE);
	outtextxy(525, 220, "NO");
	while (true)
	{
		ch = getch();
		switch (ch)
		{
		case 13: return 1;
		case 75:
		nguyen:
			setcolor(WHITE);
			//settextjustify(VCENTER_TEXT, VCENTER_TEXT);
			//settextstyle(1, LEFT_TEXT, 1);
			outtextxy(525, 220, "NO");

			setcolor(YELLOW);
			//settextjustify(VCENTER_TEXT, VCENTER_TEXT);
			//settextstyle(1, LEFT_TEXT, 1);
			outtextxy(335, 220, "YES");
			switch (getch())
			{
			case 13:
				return 1;
			case 77:
				goto nguyen1;
				break;
			}
			break;
		case 77:
		nguyen1:
			setcolor(WHITE);
			outtextxy(335, 220, "YES");
			setcolor(YELLOW);
			outtextxy(525, 220, "NO");
			switch (getch())
			{
			case 13:
				return 0;
			case 75:
				goto nguyen;
			}
		}
	}
}
int main()
{
	/*
	dohoa1(): 
	1.Output() : Giới thiệu bản thân
	2.Output1(): Quá trình download
	3.Output2(): Tạo file, nếu file chưa có thì tạo file, rồi gán vào tọa độ rắn ,food,level,speed...
	4.Output3(): Phần lựa chọn các kiểu (about,choose level(khởi tạo lại các giá trị nếu muốn),start(bắt đầu với các giá trị tương ứng),Quit(thoát trò chơi))
	*/
	dohoa1(); 
nguyenbanh:
	cleardevice();
	banglon(); // vẽ bản bao gồm khung , thức ăn , level ,speed
	ResetData(); // vẽ rắn, vẽ thức ăn,cho rắn đứng yên.
	while (true)
	{
		if (tt != DEAD)
		{
			DeleteSnake();
			Move(a, b);

			DrawSnake();
			if (Xuly_VaCham() == 1)
			{
				tt = DEAD;
				flag10 = 2; // cờ này dùng để chặn rắn chết, và để tạo bảng bangxuly()
				//break;
			}
			if (xacdinhtoadoa(a, b, food.x, food.y) == 1)
			{
				Score++;
				food_++;
				cout << "\a";
				DeleteFood(food.x, food.y);
				insert(a, b);
				char *ch = new char[5];
				sprintf(ch, "%d", Score);
				outtextxy(930, 80, ch);
				sprintf(ch, "%d", food_);
				outtextxy(930, 100, ch);
				if (food_ == 3)
				{
					Lo_den(x_1, y_1);
					while (true)
					{
						DeleteSnake();
						if (tt3 != STOP)
						{
							Move(a, b);
						}
						if (Xuly_VaCham() == 1)
						{
							if (bangxuly() == 1)
							{
								Initiazation();
								goto nguyenbanh;
							}
							else exit(0);
						}
						if (xacdinhtoadoa1(snake.dot[0].x, snake.dot[0].y, x_1, y_1) == 2 && tt2 != CONG) // vo cong
						{
							Hieu_Ung();
							tt3 = STOP;
							if (snake.n == 1)
							{
								tt3 = ALIVE;
								Xoa_Loden(x_1, y_1);
								snake.n = Score + 7;
								DeleteSnake();
								Lo_den(x_1, y_1);
								a = x_1;
								b = y_1;
								for (int i = 0; i < snake.n; i++)
								{
									snake.dot[i].x = x_1;
									snake.dot[i].y = y_1;
								}
								tt2 = CONG;
							}
						}
						else if (xacdinhtoadoa1(snake.dot[snake.n - 1].x, snake.dot[snake.n - 1].y, x_1, y_1) == 0 && tt2 != CONG) Ve_loden(x_1, y_1);
						if (tt2 == CONG && xacdinhtoadoa1(snake.dot[snake.n - 1].x, snake.dot[snake.n - 1].y, x_1, y_1) == 2) //di ra
						{
							Xoa_Loden(x_1, y_1);
							tt2 = ALIVE;
							DrawSnake();
							break;
						}
						DrawSnake();
						int sec = (float)100 / speed;
						delay(sec);
					}
					if (flag != 1)
					{
						level++;
						speed++;
						char *ch = new char[5];
						sprintf(ch, "%d", level);
						outtextxy(930, 120, ch);
						sprintf(ch, "%d", speed);
						outtextxy(930, 140, ch);
						if (speed == 4)
						{
							if (Hienthi_1("SAVE") == 0)
							{
								filegame.open(tenfile, ios_base::out);
								filegame << Score << endl;
								filegame << food_ << endl;
								filegame << level << endl;
								filegame << speed << endl;
								filegame << snake.n << endl;
								filegame << food.x << endl;
								filegame << food.y << endl;
								for (int i = 0; i < snake.n; i++)
								{
									filegame << snake.dot[i].x << endl;
									filegame << snake.dot[i].y << endl;
								}
								filegame.close();
								exit(0);
							}
							else
							{
								Initiazation();
								goto nguyenbanh;
							}
						}
					}
					food_ = 0;
					char *ch = new char[5];
					sprintf(ch, "%d", food_);
					outtextxy(930, 100, ch);
				}
				DrawFood();
			}
		int sec = (float)100 / speed;
		delay(sec);
		}
		else break;
	}

	switch (flag10)
	{
	case 2:
		if (bangxuly() == 1)
		{
			Initiazation();
			goto nguyenbanh;
		}
		else exit(0);
	case 1:
		if (Hienthi_1("CONTINUE") == 0)
		{
			goto nguyenbanh;
		}
		else
		{
			Initiazation();
			goto nguyenbanh;
		}
	case 0:
		if (Hienthi_1("SAVE") == 0)
		{
			filegame.open(tenfile, ios_base::out);
			filegame << Score << endl;
			filegame << food_ << endl;
			filegame << level << endl;
			filegame << speed << endl;
			filegame << snake.n << endl;
			filegame << food.x << endl;
			filegame << food.y << endl;
			for (int i = 0; i < snake.n; i++)
			{
				filegame << snake.dot[i].x << endl;
				filegame << snake.dot[i].y << endl;
			}
			filegame.close();
			tt = ALIVE;
			goto nguyenbanh;
		}
		else
		{
			Initiazation();
			goto nguyenbanh;
		}
	}
}