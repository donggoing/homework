//snake_eat.c
//simple snake game v0.2
//
//Created by 16307015 on 18-11-29.
//Copyright (c) 2018年 Sun Yat-Sen University.All rights reserved.
//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

//传入垂直和水平方向，蛇根据该方向上的下一物体做出不同反应
void snakeMove(int, int);
//上一个食物被吃后，在正确的位置上随机放置一个食物
void put_money(void);
//输出二维数组地图
void output(void);
//置alive为0杀死蛇并输出Game Over！
void gameover(void);
//初始化参数、蛇和地图状态
void init(void);
//延迟,使用time.h文件以兼容不同平台或编译器
void delay(int);

char map[12][12] =
{
	"************",
	"*XXXXH     *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"************"
};

int snakeX[SNAKE_MAX_LENGTH] = { 1,2,3,4,5 };
int snakeY[SNAKE_MAX_LENGTH] = { 1,1,1,1,1 };
//蛇的长度
int snakeLength = 5;
//记录当前蛇的运动方向
int curv = 0, curh = 1;
//蛇是否存活
int alive = 1;
//玩家得分
int score = 0;

int main() {
	while (1) {
		printf("按下S开始游戏:");
		char st = getch();
		while (st != 'S' && st != 's')
			st=getch();
		//初始化参数
		init();
		//清空界面
		system("cls");
		//输出界面
		output();
		while (alive) {	
			//若键盘有输入，根据输入值进行移动并更新蛇的状态和地图
			if (kbhit()) {
				char dir = getch();
				switch (dir) {
					case 'w':
					case 'W':
					snakeMove(-1, 0);
					break;
					case 's':
					case 'S':
					snakeMove(1, 0);
					break;
					case 'a':
					case 'A':
					snakeMove(0, -1);
					break;
					case 'd':
					case 'D':
					snakeMove(0, 1);
					break;
					default:
					snakeMove(curv, curh);
				}
			}
			//否则蛇按当前方向移动
			else snakeMove(curv, curh);
			//输出界面
			system("cls");
			output();
			//延迟
			delay(150);
		}
	
	}
}

//初始化游戏各参数、蛇和地图
void init() {
	alive = 1;
	score = 0;
	curv = 0;
	curh = 1;
	snakeLength = 5;
	for (int i = 1; i < 11; ++i)
		for (int j = 1; j < 11; ++j)
			map[i][j] = ' ';
	map[1][1] = map[1][2] = map[1][3] = map[1][4] = SNAKE_BODY;
	map[1][5] = SNAKE_HEAD;
	for (int i = 0; i < 5; ++i) {
		snakeX[i] = i + 1;
		snakeY[i] = 1;
	}
	put_money();
}

//输出界面
void output() {
	printf("·Score:%d·\n", score);
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j)
			printf("%c", map[i][j]);
		printf("\n");
	}
}

//延迟
void  delay(int time)//time单位为ms
{
	clock_t now = clock();
	while (clock() - now < time);
}

//snake移动，v：垂直方向，h：水平方向
void snakeMove(int v, int h) {
	int newrow = snakeY[snakeLength - 1] + v, newcol = snakeX[snakeLength - 1] + h;
	//若下一步为墙则失败，游戏结束
	if (map[newrow][newcol] == WALL_CELL)
		gameover();
	//若下一步为蛇身且方向不是当前方向的反方向则失败，游戏结束
	else if (map[newrow][newcol] == SNAKE_BODY) {
		if (v == -curv && h == -curh)return;
		else gameover();
	}
	else {
		//长度未到最大长度时继续游戏
		if (snakeLength < SNAKE_MAX_LENGTH) {
			//修改当前移动方向
			curv = v;
			curh = h;
			//如果下一步为空格时正常移动
			if (map[newrow][newcol] == BLANK_CELL) {
				map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = SNAKE_BODY;
				map[newrow][newcol] = SNAKE_HEAD;
				map[snakeY[0]][snakeX[0]] = BLANK_CELL;
				for (int i = 0; i < snakeLength - 1; ++i) {
					snakeX[i] = snakeX[i + 1];
					snakeY[i] = snakeY[i + 1];
				}
				snakeX[snakeLength - 1] = newcol;
				snakeY[snakeLength - 1] = newrow;
			}
			//若下一步为食物，蛇长度加一
			else if (map[newrow][newcol] == SNAKE_FOOD) {
				map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = SNAKE_BODY;
				map[newrow][newcol] = SNAKE_HEAD;
				map[snakeY[0]][snakeX[0]] = SNAKE_BODY;
				snakeX[snakeLength] = newcol;
				snakeY[snakeLength] = newrow;
				snakeLength += 1;
				score += 10;
				put_money();
			}
		}
		//否则停止游戏
		else {
			gameover();
			printf("Well Done But Snake Is Too Long.\n");
		}
	}
}

//随机在合适的区域放置食物
void put_money(void) {
	int r = rand() % 10 + 1, c = rand() % 10 + 1;
	while (1) {
		if (map[r][c] != SNAKE_BODY && map[r][c] != SNAKE_HEAD)break;
		r = rand() % 10 + 1, c = rand() % 10 + 1;
	}
	map[r][c] = SNAKE_FOOD;
}

//结束游戏
void gameover(void) {
	alive = 0;
	system("cls");
	printf("Game Over!\nYou got %d.\n", score);
}