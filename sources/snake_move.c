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
//延迟
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
		//输出界面
		output();
		while (alive) {
			//获取蛇的下一运动方向
			char dir = getchar();
			while (dir == '\n')dir = getchar();
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
			//输出界面
			output();
		}
	}
}

//snake移动，v：垂直方向，h：水平方向
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

//随机在合适的区域放置食物
void put_money(void) {
	printf("Put Money.\n");
}

//输出界面
void output(void) {
	printf("Print the map.\n");
}

//结束游戏
void gameover(void) {
	printf("Game Over!\n");
}

//延迟
void  delay(int time) {
	printf("Delay time s.\n");
}

//初始化游戏各参数、蛇和地图
void init() {
	printf("Initialize Game.\n");
}