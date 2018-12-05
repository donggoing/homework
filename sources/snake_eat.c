//snake_eat.c
//simple snake game v0.2
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
//�ӳ�,ʹ��time.h�ļ��Լ��ݲ�ͬƽ̨�������
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
		printf("����S��ʼ��Ϸ:");
		char st = getch();
		while (st != 'S' && st != 's')
			st=getch();
		//��ʼ������
		init();
		//��ս���
		system("cls");
		//�������
		output();
		while (alive) {	
			//�����������룬��������ֵ�����ƶ��������ߵ�״̬�͵�ͼ
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
			//�����߰���ǰ�����ƶ�
			else snakeMove(curv, curh);
			//�������
			system("cls");
			output();
			//�ӳ�
			delay(150);
		}
	
	}
}

//��ʼ����Ϸ���������ߺ͵�ͼ
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

//�������
void output() {
	printf("��Score:%d��\n", score);
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j)
			printf("%c", map[i][j]);
		printf("\n");
	}
}

//�ӳ�
void  delay(int time)//time��λΪms
{
	clock_t now = clock();
	while (clock() - now < time);
}

//snake�ƶ���v����ֱ����h��ˮƽ����
void snakeMove(int v, int h) {
	int newrow = snakeY[snakeLength - 1] + v, newcol = snakeX[snakeLength - 1] + h;
	//����һ��Ϊǽ��ʧ�ܣ���Ϸ����
	if (map[newrow][newcol] == WALL_CELL)
		gameover();
	//����һ��Ϊ�����ҷ����ǵ�ǰ����ķ�������ʧ�ܣ���Ϸ����
	else if (map[newrow][newcol] == SNAKE_BODY) {
		if (v == -curv && h == -curh)return;
		else gameover();
	}
	else {
		//����δ����󳤶�ʱ������Ϸ
		if (snakeLength < SNAKE_MAX_LENGTH) {
			//�޸ĵ�ǰ�ƶ�����
			curv = v;
			curh = h;
			//�����һ��Ϊ�ո�ʱ�����ƶ�
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
			//����һ��Ϊʳ��߳��ȼ�һ
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
		//����ֹͣ��Ϸ
		else {
			gameover();
			printf("Well Done But Snake Is Too Long.\n");
		}
	}
}

//����ں��ʵ��������ʳ��
void put_money(void) {
	int r = rand() % 10 + 1, c = rand() % 10 + 1;
	while (1) {
		if (map[r][c] != SNAKE_BODY && map[r][c] != SNAKE_HEAD)break;
		r = rand() % 10 + 1, c = rand() % 10 + 1;
	}
	map[r][c] = SNAKE_FOOD;
}

//������Ϸ
void gameover(void) {
	alive = 0;
	system("cls");
	printf("Game Over!\nYou got %d.\n", score);
}