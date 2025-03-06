#pragma once
#include <stdio.h>
#include "graphics.h" //ͼ�ο�,�������ֿ�������ͼ�α�� easyx
#include <mmsystem.h>//������ý���豸�ӿ�ͷ�ļ�,һ������graphics.h����
#pragma comment(lib,"Winmm.lib")//���ؾ�̬��
#include <conio.h>//_getch()��ͷ�ļ�������C���Եı�׼����
#include <time.h>


enum Size//���ڵĸ߶ȺͿ�
{
	//���ڳߴ�
	WIDTH = 480,
	HEIGHT = 852,

	//��ҷɻ��ߴ�
	PLAN_WIDTH = 102,
	PLAN_HEIGHT = 120,

	//�ҷ��ӵ��ߴ�
	BULLET_WIDTH = 19,
	BULLET_HEIGHT = 24,
	//�л��ӵ��ߴ�
	BULLET1_WIDTH = 20,
	BULLET1_HEIGHT = 20,
	//�ӵ���Ŀ
	BULLET_NUM = 15,
	BULLET1_NUM = 100,

	//�л���Ŀ
	ENEMY_NUM = 10,
	//�л��ߴ�
	BIG,
	SMALL,
	BIG_WIDTH = 104,
	BIG_HEIGHT = 108,
	SMALL_WIDTH = 52,
	SMALL_HEIGHT = 39,
	//�л�Ѫ��
	BIG_PH = 3,
	SMALL_PH = 1
};

#define PLAYER_SPEED 1//����ƶ��ٶ�
#define ENEMY_SPEED 1.0//�л��ƶ��ٶ�
#define BULLET_SPEED 2//�ӵ��ƶ��ٶ�
#define BULLET1_SPEED 0.4//�з��ӵ��ƶ��ٶ�

//����ͼƬ����
void loadImg();

//���ƿ�ʼ����
void drawStopScreen();

//��ϷͼƬ�Ļ��ƺ���
void gameDraw();

//���ƽ�������
void drawEndScreen();

//���ƿ�ʼ����
void drawStartScreen();

//��ҷɻ���ʼ��  �ӵ���ʼ��
void gameInit();

//��ɫ�ƶ�����ȡ������Ϣ  �ӵ��ƶ�
void playerMove(int speed);

//�����ӵ�
void creatBullet();

void creatBullet1();
//�ӵ��ƶ�
void bulletMove(int speed);

void bullet1Move(double speed);

//���õл�
void enemyHp(int i);

//create�л�
void creatEnemy();

//�л�move
void enemyMove(double speed);

//��ʱ
bool Timer(int ms, int id);

//��ɻ�
void shootPlane();

//���ӵ�����
void shootEnemy();

//��ұ�����
void Attacked();

//��Ϸ������Ϣ
void textDraw();

//���ű�������
void BGMPLAY();


