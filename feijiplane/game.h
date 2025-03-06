#pragma once
#include <stdio.h>
#include "graphics.h" //图形库,帮助新手快速入门图形编程 easyx
#include <mmsystem.h>//包含多媒体设备接口头文件,一定放在graphics.h下面
#pragma comment(lib,"Winmm.lib")//加载静态库
#include <conio.h>//_getch()的头文件，不是C语言的标准函数
#include <time.h>


enum Size//窗口的高度和宽
{
	//窗口尺寸
	WIDTH = 480,
	HEIGHT = 852,

	//玩家飞机尺寸
	PLAN_WIDTH = 102,
	PLAN_HEIGHT = 120,

	//我方子弹尺寸
	BULLET_WIDTH = 19,
	BULLET_HEIGHT = 24,
	//敌机子弹尺寸
	BULLET1_WIDTH = 20,
	BULLET1_HEIGHT = 20,
	//子弹数目
	BULLET_NUM = 15,
	BULLET1_NUM = 100,

	//敌机数目
	ENEMY_NUM = 10,
	//敌机尺寸
	BIG,
	SMALL,
	BIG_WIDTH = 104,
	BIG_HEIGHT = 108,
	SMALL_WIDTH = 52,
	SMALL_HEIGHT = 39,
	//敌机血量
	BIG_PH = 3,
	SMALL_PH = 1
};

#define PLAYER_SPEED 1//玩家移动速度
#define ENEMY_SPEED 1.0//敌机移动速度
#define BULLET_SPEED 2//子弹移动速度
#define BULLET1_SPEED 0.4//敌方子弹移动速度

//加载图片函数
void loadImg();

//绘制开始界面
void drawStopScreen();

//游戏图片的绘制函数
void gameDraw();

//绘制结束界面
void drawEndScreen();

//绘制开始界面
void drawStartScreen();

//玩家飞机初始化  子弹初始化
void gameInit();

//角色移动，获取键盘消息  子弹移动
void playerMove(int speed);

//创建子弹
void creatBullet();

void creatBullet1();
//子弹移动
void bulletMove(int speed);

void bullet1Move(double speed);

//设置敌机
void enemyHp(int i);

//create敌机
void creatEnemy();

//敌机move
void enemyMove(double speed);

//定时
bool Timer(int ms, int id);

//打飞机
void shootPlane();

//被子弹攻击
void shootEnemy();

//玩家被攻击
void Attacked();

//游戏文字信息
void textDraw();

//播放背景音乐
void BGMPLAY();


