#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include <Windows.h>
#include<graphics.h>
#include<math.h>
#include<string>
#include<iostream>
#include<fstream>
#include<algorithm>
#pragma comment(lib,"Winmm.lib")
#pragma warning(disable:4996)
#define pi 3.1415926
#define ORANGE RGB(255,128,0)
#define BK RGB(118,127,98)
#define BLOCK RGB(102,152,102)
#define WallNumber 45
#define SpecialNumber 63
#define CoinNumber 30
#define SpeedNumber 30
#define BoomNumber 3
#define MazeHeight 15
#define MazeWidth 21
#define MazeSize 45
#define HeroSize 45
#define ROAD 0
#define WALL 1
#define END 2
#define COIN 3
#define SPEED 4
#define BOOM 5
#define MARK 6
using namespace std;
int height = 50 + MazeSize * MazeHeight;
int width = 250 + MazeSize * MazeWidth;
int m[MazeHeight][MazeWidth] = { 0 };
int x = 25, y = 25;
int v = 9;
int hour = 0, minute = 2, second = 0,msec=0;
int frame = 0;
int coins=0;
int score;
int len = 0;
int num_open = 0;
int num_close = 0;
int num = 1;
char input;
bool tnt = false;
bool pass = false;
bool ex = false;
bool jump_final = false;
string str;
time_t first, now;
IMAGE background,intro1, intro2, intro3, intro4,intro5;
IMAGE Floor, Mfloor,End,Wall,Coin,Mcoin,Speed,TNTFloor,MTNTFloor,TNT,Boom2,Boom3,boom2,boom3,Cgly1,Cgly2,Lgly1,Lgly2,Rgly1,Rgly2,F;
ExMessage M;
fstream file;
struct  Player
{
	int rank;
	string name;
	int score;
};
struct node
{
	int x;
	int y;
	int g;
	int h;
	int f;
	int style;
	node* previous;
	int inopen;
	int inclose;
};
Player a[11];
void First()
{
	initgraph(width, height, 0);
	mciSendString(_T("open res//Background.mp3 alias bkgd"), NULL, 0, NULL);
	mciSendString(_T("open res//Coin'.mp3 alias coin"), NULL, 0, NULL);
	mciSendString(_T("open res//Get'.mp3 alias get"), NULL, 0, NULL);
	mciSendString(_T("open res//Boom'.mp3 alias Boom"), NULL, 0, NULL);
	mciSendString(_T("play bkgd repeat"), NULL, 0, NULL);
	loadimage(&background, _T("res//start.jpeg"));
	loadimage(&Floor, _T("res//floor1.jpg"));
	loadimage(&Mfloor, _T("res//guidefloor.jpg"));
	loadimage(&Wall, _T("res//wall2.jpg"));
	loadimage(&End, _T("res//portal.jpg"));
	loadimage(&Coin, _T("res//coin.png"));
	loadimage(&Mcoin, _T("res//Mcoin.png"));
	loadimage(&Speed, _T("res//speedup.jpg"));
	loadimage(&TNTFloor, _T("res//tnt1.png"));
	loadimage(&TNT, _T("res//tnt.png"));
	loadimage(&MTNTFloor, _T("res//Mtnt.png"));
	loadimage(&Boom2, _T("res//tnt2.png"));
	loadimage(&Boom3, _T("res//tnt3.png"));
	loadimage(&boom2, _T("res//tnt2'.png"));
	loadimage(&boom3, _T("res//tnt3'.png"));
	loadimage(&Rgly1, _T("res//resource1.png"));
	loadimage(&Rgly2, _T("res//resource1'.png"));
	loadimage(&Lgly1, _T("res//resource2.png"));
	loadimage(&Lgly2, _T("res//resource2'.png"));
	loadimage(&F, _T("res//End.png"));
	loadimage(&intro1, _T("res//intro1.png"));
	loadimage(&intro2, _T("res//intro2.png"));
	loadimage(&intro3, _T("res//intro3.png"));
	loadimage(&intro4, _T("res//intro4.png"));
	loadimage(&intro5, _T("res//intro5.png"));
	setbkmode(TRANSPARENT);
	time_t t;
	srand((unsigned)time(&t));
	putimage(0, 0, &intro1);
	_getch();
	putimage(0, 0, &intro2);
	_getch();
	putimage(0, 0, &intro3);
	_getch();
	putimage(0, 0, &intro4);
	_getch();
	putimage(0, 0, &intro5);
	_getch();
	BeginBatchDraw();
}
bool cmp(Player a, Player b)
{
	return a.score > b.score;
}
string wideCharToMultiByte(wchar_t* pWCStrKey)
{
	int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
	char* pCStrKey = new char[pSize + 1];
	WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
	pCStrKey[pSize] = '\0';
	return pCStrKey;
}
void DrawStart()
{
	setbkcolor(BK);
	cleardevice();
	putimage(0, 0, &background);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("等线"),0,0,FW_BOLD,0,0,0);
	outtextxy(width/2+200, 100, _T("地牢探险"));
	setfillcolor(BLOCK);
	solidrectangle(600+0.1*(width-600), 200, 600+0.9*(width-600), 260);
	solidrectangle(600 + 0.1 * (width - 600), 300, 600 + 0.9 * (width - 600), 360);
	solidrectangle(600 + 0.1 * (width - 600), 400, 600 + 0.9 * (width - 600), 460);
	solidrectangle(600 + 0.1 * (width - 600), 500, 600 + 0.9 * (width - 600), 560);
	settextstyle(30, 0, _T("等线"),0,0,FW_LIGHT,0,0,0);
	outtextxy(540 + 0.5 * (width - 600), 215, _T("开始游戏"));
	outtextxy(540 + 0.5 * (width - 600), 315, _T("游戏说明"));
	outtextxy(525 + 0.5 * (width - 600), 415, _T("游戏排行榜"));
	outtextxy(540 + 0.5 * (width - 600), 515, _T("退出游戏"));
}
void DrawPath(int m[MazeHeight][MazeWidth],int x,int y)
{
	int direction, dx, dy;
	int a[4] = { 0,1,2,3 };
	for (int i = 0; i < 4; i++)
	{
		direction = rand() % 4;
		int temp = a[direction];
		a[direction] = a[i];
		a[i] = temp;
	}
	m[y][x] = ROAD;
	for (int i = 0; i < 4; i++)
	{
		dx = round(cos(a[i] * pi / 2));
		dy = round(sin(a[i] * pi / 2));
		if (x + 2 * dx < MazeWidth && x + 2 * dx >= 0 && y + 2 * dy < MazeHeight && y + 2 * dy >= 0 && m[y + 2 * dy][x + 2 * dx] == WALL)
		{
			m[y + dy][x + dx] = ROAD;
			DrawPath(m, x + 2 * dx, y + 2 * dy);
		}
	}
}
void GenerateMatrix(int m[MazeHeight][MazeWidth],int x,int y )
{
	for (int i = 0; i < MazeHeight; i++)
	{
		for (int j = 0; j < MazeWidth; j++)
				m[i][j] = WALL;
	}
	DrawPath(m,x,y);
	m[MazeHeight - 1][MazeWidth - 1] = END;
	for (int i = 0; i < MazeHeight; i++)
	{
		for (int j = 0; j < MazeWidth; j++)
		{
			if (m[i][j] == ROAD)
			{
				int r = rand() % (MazeHeight*MazeWidth);
				if (r < SpecialNumber)
				{
					r = rand() % SpecialNumber;
					if (r < CoinNumber)
						m[i][j] = COIN;
					else if (r<SpecialNumber-BoomNumber)
						m[i][j] = SPEED;
					else
						m[i][j] = BOOM;
				}
			}
		}
	}
}
void DrawMap()
{
	for (int i = 0; i < MazeHeight; i++)
	{
		for (int j = 0; j < MazeWidth; j++)
		{
			if (m[i][j] == WALL)
				putimage(25 + j * MazeSize, 25 + i * MazeSize, &Wall);	
			else if (m[i][j] == ROAD || m[i][j] == COIN)
			{
				putimage(25 + j * MazeSize, 25 + i * MazeSize, &Floor);
				if (m[i][j] == COIN)
					putimage(30 + j * MazeSize, 30 + i * MazeSize, &Coin);
			}
			else if (m[i][j] == END)
				putimage(25 + j * MazeSize, 25 + i * MazeSize, &End);
			else if (m[i][j] == SPEED)
				putimage(25 + j * MazeSize, 25 + i * MazeSize, &Speed);
			else if(m[i][j]==BOOM)
				putimage(25 + j * MazeSize, 25 + i * MazeSize, &TNTFloor);
			else if (m[i][j] >= MARK)
			{
				int x = m[i][j] - MARK;
				if (x == ROAD)
					putimage(25 + j * MazeSize, 25 + i * MazeSize, &Mfloor);
				else if (x == COIN)
				{
					putimage(25 + j * MazeSize, 25 + i * MazeSize, &Mfloor);
					putimage(30 + j * MazeSize, 30 + i * MazeSize, &Mcoin);
				}
				else if (x == BOOM)
				{
					putimage(25 + j * MazeSize, 25 + i * MazeSize, &MTNTFloor);
				}
				else if (x == SPEED)
					m[i][j] -= MARK;
				else if (x == END)
					m[i][j] -= MARK;
			}
		}
	}
}
void DrawHero(int x,int y,int i,bool tnt)
{
	putimage(x, y, 45, 45, &Cgly2,45 * (i % 4), 45 * (i / 4), NOTSRCERASE);
	putimage(x, y, 45, 45,&Cgly1, 45*(i%4), 45*(i/4), SRCINVERT);
	if (tnt)
		putimage(x+10, y+20, &TNT);
	
}
void DrawRank()
{
	cleardevice();
	setfillcolor(BLOCK);
	solidrectangle(50, 8 * height/ 10 , 300, 9* height / 10 );
	settextstyle(40, 0, _T("等线"));
	settextcolor(BLACK);
	outtextxy(135, 8.5 * height / 10 - 20, _T("返回"));
	file.open("rank.txt", ios::in);
	Player temp;
	for (int i = 0; i < 10; i++)
	{
		file >> temp.rank >> temp.name >> temp.score;
		if (temp.rank == i+1)
		{
			TCHAR s[100];
			wsprintf(s, _T("%d %hs %d"), temp.rank, temp.name.c_str(), temp.score);
			outtextxy(width/2, 50+i * height / 11, s);
		}
		else
			break;
	}
	file.close();
	FlushBatchDraw();
	while (true)
	{
		M = getmessage(EM_MOUSE);
		if (M.message == WM_LBUTTONDOWN)
		{
			if (M.x >= 50 && M.x <= 300 && M.y >= 8 * height / 10 && M.y <= 9 * height / 10)
				return;
		}
	}
}
void DrawIntro() 
{
	cleardevice();
	putimage(0, 0, &intro4);
	FlushBatchDraw();
	_getch();
	putimage(0, 0, &intro5);
	FlushBatchDraw();
	_getch();
}
void startup()
{
	Cgly1 = Rgly1;
	Cgly2 = Rgly2;
	score = 0;
	coins = 0;
	frame = 0;
	tnt = false;
	pass = false;
	jump_final = false;
	x = 25;
	y = 25;
	v = 9;
	hour = 0;
	minute = 2;
	second = 0;
	msec = 0;
	len = 0;
	input = 0;
	num_open = 0;
	num_close = 0;
	num = 1;
	setbkcolor(WHITE);
	cleardevice();
	DrawStart();
	FlushBatchDraw();
	while (true)
	{
		M = getmessage(EM_MOUSE);
		if (M.message == WM_LBUTTONDOWN)
		{
			if (M.x >= 600 + 0.1 * (width - 600) && M.x <= 600 + 0.9 * (width - 600) && M.y >= 200 && M.y <= 260)
				break;
			if (M.x >= 600 + 0.1 * (width - 600) && M.x <= 600 + 0.9 * (width - 600) && M.y >= 500 && M.y <= 560)
			{
				ex = true;
				return;
			}
			if (M.x >= 600 + 0.1 * (width - 600) && M.x <= 600 + 0.9 * (width - 600) && M.y >= 400 && M.y <= 460)
			{
				DrawRank();
				cleardevice();
				DrawStart();
				FlushBatchDraw();
			}
			if (M.x >= 600 + 0.1 * (width - 600) && M.x <= 600 + 0.9 * (width - 600) && M.y >= 300 && M.y <= 360)
			{
				DrawIntro();
				cleardevice();
				DrawStart();
				FlushBatchDraw();
			}
		}
	}
	GenerateMatrix(m, MazeWidth - 1, MazeHeight - 1);
	setbkcolor(WHITE);
	cleardevice();
	DrawMap();
	FlushBatchDraw();
	DrawHero(x,y,3,tnt);
	FlushBatchDraw();
}
node* open[MazeHeight * MazeWidth];
node* close[MazeHeight * MazeWidth];
node maze[MazeHeight][MazeWidth];
void adjust_heap(int i, int ed)
{
	int parent = i;
	int child = 2 * parent + 1;
	node* tmp = open[i];
	while (child <= ed)
	{
		if (child + 1 <= ed && open[child]->f > open[child + 1]->f)
			child++;
		if (tmp->f < open[child]->f)				
			break;
		else
		{
			open[parent] = open[child];			
			parent = child;
			child = 2 * parent + 1;
		}
	}
	open[parent] = tmp;
}
void insertopen(node* next, node* curr, node* end, int w)
{
	if ((next->style != WALL) && (next->inclose == 0))
	{
		if (next->inopen == 1)
		{
			if (next->f > curr->f + w)
			{
				next->f = curr->f + w;
				next->previous = curr;
				next->g = curr->g + w;
			}
		}
		else
		{
			next->g = curr->g + w;
			next->h = abs(next->x - end->x) + abs(next->y - end->y);
			next->f = next->g + next->h;
			next->previous = curr;
			next->inopen = 1;
			open[num_open++] = next;
		}

		for (int i = num_open / 2 - 1; i >= 0; i--)
			adjust_heap(i, num_open - 1);
	}
}
bool isinmap(int x, int y)
{
	bool ans = false;
	if (x >= 0 && x < MazeWidth && y >= 0 && y < MazeHeight)
		ans = true;
	return ans;
}
void consideradj(node* curr, node* end)
{
	node* next = NULL;
	if (isinmap(curr->x + 1, curr->y))
	{
		next = &maze[curr->y][curr->x + 1];
		insertopen(next, curr, end, 1);
	}
	if (isinmap(curr->x - 1, curr->y))
	{
		next = &maze[curr->y][curr->x - 1];
		insertopen(next, curr, end, 1);
	}
	if (isinmap(curr->x, curr->y + 1))
	{
		next = &maze[curr->y + 1][curr->x];
		insertopen(next, curr, end, 1);
	}
	if (isinmap(curr->x, curr->y - 1))
	{
		next = &maze[curr->y - 1][curr->x];
		insertopen(next, curr, end, 1);
	}
}
void Astar(int a[MazeHeight][MazeWidth], int starti, int startj, int endi, int endj)
{
	for (int i = 0; i < MazeHeight; i++)
	{
		for (int j = 0; j < MazeWidth; j++)
		{
			if (a[i][j] >= MARK)
				a[i][j] -= MARK;
		}
	}
	for (int i = 0; i < MazeHeight; i++)
		for (int j = 0; j < MazeWidth; j++)
		{
			maze[i][j].x = j;
			maze[i][j].y = i;
			maze[i][j].g = 0;
			maze[i][j].h = abs(i - endi) + abs(j - endj);
			maze[i][j].f = maze[i][j].g + maze[i][j].h;
			maze[i][j].style = a[i][j];
			maze[i][j].previous = NULL;
			maze[i][j].inopen = 0;
			maze[i][j].inclose = 0;
		}

	node* start = &maze[starti][startj], * end = &maze[endi][endj], * curr = start;
	bool isfound = false;

	start->previous = NULL;
	start->inopen = 1;
	open[num_open++] = start;


	while (true)
	{
		curr = open[0];
		open[0] = open[num_open - 1];
		num_open--;
		adjust_heap(0, num_open - 1);
		close[num_close++] = curr;
		curr->inclose = 1;

		if (curr->x == end->x && curr->y == end->y)
		{
			isfound = true;
			break;
		}

		consideradj(curr, end);

		if (num_open == 0)
		{
			isfound = false;
			break;
		}
	}
	if (isfound)
	{
		int top = 0;
		node* p = end;
		while (p)
		{
			if (p == start)
				break;
			a[p->y][p->x] += MARK;
			p = p->previous;
		}
	}
}
void ShowTimer()
{
	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(RED);
	TCHAR s[10];
	wsprintf(s, _T("%02d:%02d:%02d"), hour,minute,second);
	outtextxy(width - 160, height / 2 - 30, s);
}
void ShowCoins()
{
	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(ORANGE);
	TCHAR s[10];
	wsprintf(s, _T("金币数：%02d"), coins);
	outtextxy(width - 175, height / 2, s);
}
void ShowScores()
{
	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(BLUE);
	TCHAR s[10];
	wsprintf(s, _T("得分：%3d"), score);
	outtextxy(width - 170, height / 2+30, s);
}
void show()
{
	ShowTimer();
	ShowCoins();
	ShowScores();
	FlushBatchDraw();
	clearrectangle(width - 200, 0, width-1, height-1);
	ShowTimer();
	ShowCoins();
	ShowScores();
	FlushBatchDraw();
}
void Countdown()
{
	msec -= 100;
	if (msec < 0)
	{
		msec += 1000;
		second--;
	}
	if (second < 0)
	{
		second += 60;
		minute--;
	}
	if (minute < 0)
	{
		if (hour > 0)
		{
			minute += 60;
			hour--;
		}
	}
}
void updateWithoutInput()
{
	Countdown();
	score = hour * 3600 + minute * 60 + second + coins * 5;
	int i = (y - 25) / MazeSize;
	int j = (x - 25) / MazeSize;
	if (m[i][j] == COIN||m[i][j]==MARK+COIN)
	{
		coins++;
		m[i][j] -= COIN;
		mciSendString(_T("close coin"), NULL, 0, NULL);
		mciSendString(_T("open res//Coin'.mp3 alias coin"), NULL, 0, NULL);
		mciSendString(_T("play coin"), NULL, 0, NULL);
	}
	if (m[i][j] == SPEED)
	{
		v =15;
		first = time(NULL);
	}
	now = time(NULL);
	if (difftime(now, first) == 5)
		v = 9;
	if ((m[i][j] == BOOM||m[i][j]==MARK+BOOM) && !tnt)
	{
		m[i][j] -= BOOM;
		tnt = true;
		mciSendString(_T("close get"), NULL, 0, NULL);
		mciSendString(_T("open res//Get'.mp3 alias get"), NULL, 0, NULL);
		mciSendString(_T("play get"), NULL, 0, NULL);
	}
}
void updateWithInput()
{
	if (_kbhit())
	{
		input = _getch();
		int p1 = (y - 25) / MazeSize;
		int p2 = (y - 25 + HeroSize) / MazeSize;
		int P = (y - 2.5) / MazeSize;
		if ((y - 25) % MazeSize == 0)
			p2--;
		int q1 = (x - 25) / MazeSize;
		int q2 = (x - 25 + HeroSize) / MazeSize;
		int Q = (x - 2.5) / MazeSize;
		int p,q;
		if ((x - 25) % MazeSize == 0)
			q2--;
		switch (input)
		{
		case 'd':
			clearrectangle(x, y, x + HeroSize, y + HeroSize);
			DrawMap();
			frame++;
			frame %= 8;
			q = (x + v - 25 + HeroSize) / MazeSize;
			if (m[p1][q] == WALL || m[p2][q] == WALL || q > MazeWidth - 1)
				x = 25 + (q - 1) * MazeSize;
			else
				x += v;
			Cgly1 = Rgly1;
			Cgly2 = Rgly2;
			DrawHero(x, y, frame, tnt);
			FlushBatchDraw();
			Sleep(100);
			break;
		case 'l':
			clearrectangle(x, y, x + HeroSize, y + HeroSize);
			DrawMap();
			frame++;
			frame %= 8;
			q = (x - 24 + HeroSize) / MazeSize;
			if (m[p1][q] == WALL || m[p2][q] == WALL || q > MazeWidth - 1)
				x = 25 + (q - 1) * MazeSize;
			else
				x += 1;
			Cgly1 = Rgly1;
			Cgly2 = Rgly2;
			DrawHero(x, y, frame, tnt);
			FlushBatchDraw();
			Sleep(100);
			break;
		case 's':
			clearrectangle(x, y, x + HeroSize, y + HeroSize);
			DrawMap();
			frame++;
			frame %= 8;
			p = (y + v - 25 + HeroSize) / MazeSize;
			if (m[p][q1] == WALL || m[p][q2] == WALL || p > MazeHeight - 1)
				y = 25 + (p - 1) * MazeSize;
			else
				y += v;
			DrawHero(x, y, frame, tnt);
			FlushBatchDraw();
			Sleep(100);
			break;
		case 'k':
			clearrectangle(x, y, x + HeroSize, y + HeroSize);
			DrawMap();
			frame++;
			frame %= 8;
			p = (y - 24 + HeroSize) / MazeSize;
			if (m[p][q1] == WALL || m[p][q2] == WALL || p > MazeHeight - 1)
				y = 25 + (p - 1) * MazeSize;
			else
				y += 1;
			DrawHero(x, y, frame, tnt);
			FlushBatchDraw();
			Sleep(100);
			break;
		case 'w':
			clearrectangle(x, y, x + HeroSize, y + HeroSize);
			DrawMap();
			frame++;
			frame %= 8;
			p = (y - v - 25) / MazeSize;
			if (m[p][q1] == WALL || m[p][q2] == WALL)
				y = 25 + (p + 1) * MazeSize;
			else if (y - v < 25)
				y = 25;
			else
				y -= v;
			DrawHero(x, y, frame, tnt);
			FlushBatchDraw();
			Sleep(100);
			break;
		case 'i':
			clearrectangle(x, y, x + HeroSize, y + HeroSize);
			DrawMap();
			frame++;
			frame %= 8;
			p = (y - 26) / MazeSize;
			if (m[p][q1] == WALL || m[p][q2] == WALL)
				y = 25 + (p + 1) * MazeSize;
			else if (y - 1 < 25)
				y = 25;
			else
				y -= 1;
			DrawHero(x, y, frame, tnt);
			FlushBatchDraw();
			Sleep(100);
			break;
		case 'a':
			clearrectangle(x, y, x + HeroSize, y + HeroSize);
			DrawMap();
			frame++;
			frame %= 8;
			q = (x - v - 25) / MazeSize;
			if (m[p1][q] == WALL || m[p2][q] == WALL)
				x = 25 + (q + 1) * MazeSize;
			else if (x - v < 25)
				x = 25;
			else
				x -= v;
			Cgly1 = Lgly1;
			Cgly2 = Lgly2;
			DrawHero(x, y, frame, tnt);
			FlushBatchDraw();
			Sleep(100);
			break;
		case 'j':
			clearrectangle(x, y, x + HeroSize, y + HeroSize);
			DrawMap();
			frame++;
			frame %= 8;
			q = (x - 26) / MazeSize;
			if (m[p1][q] == WALL || m[p2][q] == WALL)
				x = 25 + (q + 1) * MazeSize;
			else if (x - 1 < 25)
				x = 25;
			else
				x -= 1;
			Cgly1 = Lgly1;
			Cgly2 = Lgly2;
			DrawHero(x, y, frame, tnt);
			FlushBatchDraw();
			Sleep(100);
			break;
		case ' ':
			if (tnt)
			{
				tnt = false;
				mciSendString(_T("close Boom"), NULL, 0, NULL);
				mciSendString(_T("open res//Boom'.mp3 alias Boom"), NULL, 0, NULL);
				mciSendString(_T("play Boom"), NULL, 0, NULL);
				putimage(x - 45, y - 45, &boom3, NOTSRCERASE);
				putimage(x - 45, y - 45, &Boom3, SRCINVERT);
				FlushBatchDraw();
				Sleep(100);
				putimage(x - 45, y - 45, &boom2, NOTSRCERASE);
				putimage(x - 45, y - 45, &Boom2, SRCINVERT);
				FlushBatchDraw();
				Sleep(100);
				putimage(x - 45, y - 45, &boom3, NOTSRCERASE);
				putimage(x - 45, y - 45, &Boom3, SRCINVERT);
				Sleep(100);
				FlushBatchDraw();
				clearrectangle(x - 45, y - 45, x + 90, y + 90);
				for (int i = P - 1; i <= P + 1; i++)
				{
					for (int j = Q - 1; j <= Q + 1; j++)
					{
						if (i >= 0 && i < MazeHeight && j >= 0 && j < MazeWidth)
						{
							if (m[i][j] == WALL)
								m[i][j] = ROAD;
						}
					}
				}
				DrawMap();
				FlushBatchDraw();
			}
			else
			{
				DrawHero(x, y, frame, tnt);
				FlushBatchDraw();
				Sleep(100);
			}
			break;
		case 'p':
			if (num)
			{
				Astar(m, P, Q, MazeHeight - 1, MazeWidth - 1);
				DrawMap();
				FlushBatchDraw();
				num--;
			}
			break;
		case 27:
			jump_final = true;
			break;
		default:
			DrawHero(x, y, frame,tnt);
			FlushBatchDraw();
			Sleep(100);
			break;
		}
	}
	else
	{
		DrawHero(x, y, frame,tnt);
		FlushBatchDraw();
		Sleep(100);
	}
}
bool IsGameOver()
{
	if (input == 27)
		return true;
	if (minute < 0 && hour == 0)
	{
		second++;
		return true;
	}
	if (x == 25 + MazeSize * (MazeWidth - 1) && y == 25 + MazeSize * (MazeHeight - 1))
	{
		pass = true;
		return true;
	}
	return false;
}
void Final()
{
	setbkcolor(BLACK);
	cleardevice();
	putimage(0, 0, &F);
	settextstyle(50, 0, _T("微软雅黑"));
	settextcolor(RED);
	score = hour * 3600 + minute * 60 + second + coins * 5;
	if (pass)
	{
		outtextxy((width-550)/2 + 390, height / 2 - 100,_T("恭喜你，通关了！"));
		score += 50;
	}
	else
		outtextxy((width - 550) / 2 + 250, height / 2 - 100, _T("很遗憾，没有在规定时间内完成！"));
	TCHAR s[10];
	wsprintf(s, _T("得分：%3d"), score);
	outtextxy((width - 550) / 2 + 430, height / 2 - 50,s);
	setfillcolor(RED);
	settextcolor(WHITE);
	settextstyle(50, 0, _T("微软雅黑"));
	solidrectangle((width - 550) * 0.1 + 550, height / 2 + 50, (width - 550) * 0.45+550, height / 2 + 100);
	solidrectangle((width - 550) * 0.55 + 550, height / 2 + 50, (width - 550) * 0.9+550, height / 2 + 100);
	outtextxy((width - 550) * 0.275 + 470, height / 2 + 50, _T("再来一局"));
	outtextxy((width - 550) * 0.725 + 470, height / 2 + 50, _T("退出游戏"));
	FlushBatchDraw();
	file.open("rank.txt",ios::in);
	wchar_t S[10];
	for (int i = 0; i < 10; i++)
	{
		file >> a[i].rank >> a[i].name >> a[i].score;
		if (a[i].rank != 0)
			len++;
	}
	InputBox(S,20,L"请输入用户名以进入排行榜：");
	Player temp;
	temp.score = score;
	str=wideCharToMultiByte(S);
	temp.name = str;
	file.close();
	file.open("rank.txt", ios::out);
	a[len] = temp;
	sort(a, a + len+1, cmp);
	for (int i = 0; i < len+1; i++)
	{
		a[i].rank = i + 1;
		file << a[i].rank << " " << a[i].name << " " << a[i].score << endl;
	}
	file.close();
	while (true)
	{
		M = getmessage(EM_MOUSE);
		if (M.message == WM_LBUTTONDOWN)
		{
			if (M.x >= (width - 550) * 0.1 + 550 && M.x <= (width - 550) * 0.45 + 550 && M.y >= height / 2 + 50 && M.y <= height / 2 + 100)
				break;
			else if (M.x >= (width - 550) * 0.45 + 550 && M.x <= (width - 550) * 0.9 + 550 && M.y >= height / 2 + 50 && M.y <= height / 2 + 100)
			{
				ex = true;
				break;
			}
		}
	}
}
int main()
{
	First();
	do
	{
		startup();
		if (ex)
			break;
		while (!IsGameOver())
		{
			show();
			updateWithInput();
			updateWithoutInput();
		}
		if(!jump_final)
			Final();
	} while (!ex);		
	EndBatchDraw();
	closegraph();
	return 0;
}