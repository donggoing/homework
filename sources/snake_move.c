//snake_move.c
//simple snake game v0.1
//
//Created by 16307015 on 18-11-29.
//Copyright (c) 2018�� Sun Yat-Sen University.All rights reserved.
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

//���봹ֱ��ˮƽ�����߸��ݸ÷����ϵ���һ����������ͬ��Ӧ
void snakeMove(int, int);
//��һ��ʳ�ﱻ�Ժ�����ȷ��λ�����������һ��ʳ��
void put_money(void);
//�����ά�����ͼ
void output(void);
//��aliveΪ0ɱ���߲����Game Over��
void gameover(void);
//��ʼ���������ߺ͵�ͼ״̬
void init(void);
//�ӳ�
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
//�ߵĳ���
int snakeLength = 5;
//��¼��ǰ�ߵ��˶�����
int curv = 0, curh = 1;
//���Ƿ���
int alive = 1;
//��ҵ÷�
int score = 0;

int main() {
	while (1) {
		printf("������S��ʼ��Ϸ!\n");
		char st = getchar();
		while (st != 'S' && st != 's')
			st = getchar();
		//�������
		output();
		while (alive) {
			//��ȡ�ߵ���һ�˶�����
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
			//�������
			output();
		}
	}
}

//snake�ƶ���v����ֱ����h��ˮƽ����
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

//����ں��ʵ��������ʳ��
void put_money(void) {
	printf("Put Money.\n");
}

//�������
void output(void) {
	printf("Print the map.\n");
}

//������Ϸ
void gameover(void) {
	printf("Game Over!\n");
}

//�ӳ�
void  delay(int time) {
	printf("Delay time s.\n");
}

//��ʼ����Ϸ���������ߺ͵�ͼ
void init() {
	printf("Initialize Game.\n");
}