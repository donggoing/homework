//snake_move.c
//simple snake game v0.1
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
		printf("请输入S开始游戏!\n");
		char st = getchar();
		while (st != 'S' && st != 's')
			st = getchar();
			output();
		while (alive) {
			char dir = getchar();
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
			}
			snakeMove(curv, curh);
			output();
		}
	}
}

void snakeMove(int v, int h) {
	if (v == -1) {
		curv = v;
		curh = h;
		printf("Sneak goes up.\n");
	}
	else if (v == 1) {
		curv = v;
		curh = h;
		printf("Sneak goes down.\n");
	}
	else if (h == -1) {
		curv = v;
		curh = h;
		printf("Sneak goes left.\n");
	}
	else {
		curv = v;
		curh = h;
		printf("Sneak goes right.\n");
	}
}
void put_money(void) {
	printf("Put Money.\n");
}
void output(void) {
	printf("Print the map.\n");
}

void gameover(void) {
	printf("Game Over!\n");
}

void  delay(int time) {
	printf("Delay time s.\n");
}

void init() {
	printf("Initialize Game.\n");
}