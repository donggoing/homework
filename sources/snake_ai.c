//snake_eat.c
//simple snake game v0.2
//
//Created by 16307015 on 18-11-29.
//Copyright (c) 2018年 Sun Yat-Sen University.All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>

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

char map[12][12] =
{
	"************",
	"*XXXXH     *",
	"*          *",
	"*          *",
	"*          *",
	"*    *     *",
	"*    *     *",
	"*      *   *",
	"* *        *",
	"*       *  *",
	"*          *",
	"************"
};

int snakeX[SNAKE_MAX_LENGTH] = { 1,2,3,4,5 };
int snakeY[SNAKE_MAX_LENGTH] = { 1,1,1,1,1 };
int direct[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
//蛇的长度
int snakeLength = 5;
//记录当前蛇的运动方向
int curv = 0, curh = 1;
//蛇是否存活
int alive = 1;
//玩家得分
int score = 0;
int Fx=5,Fy=5;

static struct termios ori_attr, cur_attr;

static __inline 
int tty_reset(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &ori_attr) != 0)
			return -1;

	return 0;
}


static __inline
int tty_set(void)
{
        
	if ( tcgetattr(STDIN_FILENO, &ori_attr) )
		return -1;
	
	memcpy(&cur_attr, &ori_attr, sizeof(cur_attr) );
	cur_attr.c_lflag &= ~ICANON;
//        cur_attr.c_lflag |= ECHO;
	cur_attr.c_lflag &= ~ECHO;
	cur_attr.c_cc[VMIN] = 1;
	cur_attr.c_cc[VTIME] = 0;

	if (tcsetattr(STDIN_FILENO, TCSANOW, &cur_attr) != 0)
			return -1;

	return 0;
}

int getch(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;
 
     if (tcgetattr(fd, &tm) < 0) {//保存现在的终端设置
          return -1;
     }
 
     tm_old = tm;
     cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {//设置上更改之后的设置
          return -1;
     }

     ch = getchar();
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//更改设置为最初的样子
          return -1;
     }
    
     return ch;
}

static __inline
int kbhit(void) 
{
                   
        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        /* Wait up to five seconds. */
        tv.tv_sec  = 0;
        tv.tv_usec = 0;

        retval = select(1, &rfds, NULL, NULL, &tv);
        /* Don't rely on the value of tv now! */

        if (retval == -1) {
                perror("select()");
                return 0;
        } else if (retval)
                return 1;
        /* FD_ISSET(0, &rfds) will be true. */
        else
                return 0;
        return 0;
}


// Fx,Fy：食物的位置
char whereGoNext() {
// 用数组movable[3]={“a”,”d”,”w”,”s”} 记录可走的方向
// 用数组distance[3]={0,0,0,0} 记录离食物的距离
// 分别计算蛇头周边四个位置到食物的距离。H头的位置，F食物位置
//     例如：假设输入”a” 则distance[0] = |Fx – (Hx-1)| + |Fy – Hy|
//           如果 Hx-1，Hy 位置不是Blank，则 distance[0] = 9999
// 选择distance中存最小距离的下标p，注意最小距离不能是9999
// 返回 movable[p]
	char movable[4]={'w','s','a','d'};
	int distance[4]={0,0,0,0};
	int dir=0;
	int Hx=snakeX[snakeLength-1],Hy=snakeY[snakeLength-1];
	for(int i=0;i<4;i++){
		char nexty=Hy+direct[i][0],nextx=Hx+direct[i][1];
		if(map[nexty][nextx]==SNAKE_BODY||map[nexty][nextx]==WALL_CELL)distance[i]=9999;
		else{
			distance[i]=abs(Fx-nextx)+abs(Fy-nexty);
			if(distance[i]<distance[dir])dir=i;
		}
	}
	return movable[dir];
}

int main()
{
        //设置终端进入非缓冲状态
        int tty_set_flag;
        tty_set_flag = tty_set();
		int end=0;
        while (!end) {
		printf("按下S后开始游戏(q结束):");
		char st = getch();
		if(st=='q'||st=='Q'){
				end=1;
				break;
		}
		while (st != 'S' && st != 's'){
			st=getch();//非window.h，自行撰写的
			if(st=='q'||st=='Q'){
				end=1;
				break;
			}
		}
		if (st == 'S' || st == 's') {
			//初始化参数
			init();
			while (alive&&!end) {
				//清空界面
				printf("\033[2J");
				//输出界面
				output();
				
				char dir = whereGoNext();
				switch (dir) {
					case 'w':
					snakeMove(-1, 0);
					break;
					case 's':
					snakeMove(1, 0);
					break;
					case 'a':
					snakeMove(0, -1);
					break;
					case 'd':
					snakeMove(0, 1);
					break;
				}
				
				//延迟
				sleep(1);
			}
		}
	}
	printf("退出游戏\n");
        //恢复终端设置
        if(tty_set_flag == 0) 
                tty_reset();
        return 0;
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
	Fx=c;
	Fy=r;
}

//结束游戏
void gameover(void) {
	alive = 0;
	printf("\033[2J");
	printf("Game Over!\nYou got %d.\n", score);
}
