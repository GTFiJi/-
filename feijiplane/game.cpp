#define _CRT_SECURE_NO_WARNINGS

#include "game.h"
#include "graphics.h"


//��ͼƬ���ؽ�����
IMAGE bk;//����ͼƬ
IMAGE bk1;
IMAGE bk2;
IMAGE bk3;
IMAGE photo[2];//��ʼ�����ͼƬ
IMAGE img_role[2];//���ͼƬ
IMAGE img_bullet[2];//�ӵ�ͼƬ
IMAGE img_bullet1[2];//�з��ӵ�ͼƬ
IMAGE img_enemy[2][2];//�л�ͼƬ
IMAGE imgdieplane[2];//��ҷɻ�����ͼƬ


void loadImg()
{
	//���ر���ͼƬ 480 * 852
	loadimage(&bk, _T("./images/background.jpg"));	loadimage(&bk1, _T("./images/background1.jpg"));
	//���س�ʼ����ͼƬ
	loadimage(&photo[0], _T("./images/R.jpg"));
	loadimage(&photo[1], _T("./images/space.jpg"));
	//loadimage(&bk1, _T("./images/background1.jpg"));//��������

	//���صл���ͼƬ
	//��
	loadimage(&img_enemy[0][0], _T("./images/enemyda1.jpg"));//����ͼ
	loadimage(&img_enemy[0][1], _T("./images/enemyda.jpg"));//ԭͼ
	//С
	loadimage(&img_enemy[1][0], _T("./images/enemy_1.jpg"));//����ͼ
	loadimage(&img_enemy[1][1], _T("./images/enemy_2.jpg"));//ԭͼ

	//�������ͼƬ
	loadimage(&img_role[0], _T("./images/hero2.jpg"));//����ͼ�����ͷ�һ�ź���
	loadimage(&img_role[1], _T("./images/hero1.jpg"));//ԭͼ

	//��������ӵ�ͼƬ
	loadimage(&img_bullet[0], _T("./images/bullet2.jpg"));//����ͼ
	loadimage(&img_bullet[1], _T("./images/bullet1.jpg"));//ԭͼ

	//���صз��ӵ�ͼƬ
	loadimage(&img_bullet1[0], _T("./images/bullet11.jpg"));//����ͼ
	loadimage(&img_bullet1[1], _T("./images/bullet12.jpg"));//ԭͼ
	//�ɻ���ըͼƬ
	loadimage(&imgdieplane[0], _T("./images/planeExplode1.jpg"));//����ͼ
	loadimage(&imgdieplane[1], _T("./images/planeExplode2.jpg"));//ԭͼ

}
struct plane//��ҷɻ���л�
{
	int x;//x����
	int y;//y����
	bool live;//�Ƿ���
	int width;//���
	int height;//�߶�
	int hp;//Ѫ��
	int type;//�л����� big small
	int score;//�÷�
}player, enemy[1000];

struct bullet//�ҷ��ӵ�
{
	int x;
	int y;
	bool live;//�Ƿ���
}bull[BULLET_NUM];

struct bullet1//�о��ӵ�
{
	double x;
	double y;
	bool live;
}bull1[BULLET1_NUM];

bool isExpolde = false; // �ɻ��Ƿ�ը
bool AlreadyOver = false;

void gameDraw()
{

	//�ѱ���ͼմ��������
	putimage(0, 0, &bk);

	//������ҷɻ� 
	//͸����ͼ������������ͼ��ԭͼ��һ����ɫ�Ķ����Ʋ���
	if (!isExpolde)
	{
		//��ҷɻ�û�б�ը������hp
		putimage(player.x, player.y, &img_role[0], NOTSRCERASE);
		putimage(player.x, player.y, &img_role[1], SRCINVERT);
	}
	else
	{
		//��ҷɻ���hp�˱�ը��
		putimage(player.x, player.y, &imgdieplane[0], NOTSRCERASE);
		putimage(player.x, player.y, &imgdieplane[1], SRCINVERT);
		Sleep(2000);//��Ϸ����
	}

	//�����ҷ��ӵ�
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bull[i].live)
		{
			putimage(bull[i].x, bull[i].y, &img_bullet[0], NOTSRCERASE);
			putimage(bull[i].x, bull[i].y, &img_bullet[1], SRCINVERT);
		}
	}
	//���Ƶз��ӵ�
	for (int i = 0; i < BULLET1_NUM; i++)
	{
		if (bull1[i].live)
		{
			putimage(bull1[i].x, bull1[i].y, &img_bullet1[0], NOTSRCERASE);
			putimage(bull1[i].x, bull1[i].y, &img_bullet1[1], SRCINVERT);
		}
	}

	//���Ƶл�
	for (int i = 0; i < ENEMY_NUM+player.score; i++)
	{
		if (enemy[i].live)
		{
			if (enemy[i].type == BIG)
			{
				//��ɻ���ͼ
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][1], SRCINVERT);
			}
			else
			{
				//С�ɻ���ͼ
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][1], SRCINVERT);
			}
		}
	}
}
bool restarting = true;
void gameInit()
{
	if (restarting)//restarting��Ϊ�ж��Ƿ��ʼ
	{

		//��ҳ�ʼ��
		player.x = WIDTH / 2- PLAN_WIDTH/2;
		player.y = HEIGHT - PLAN_HEIGHT;
		player.live = true;
		player.hp = 15;
		player.score = 0;
		player.height = PLAN_HEIGHT;
		player.width = PLAN_WIDTH;

		//�ҷ��ӵ���ʼ��
		for (int i = 0; i < BULLET_NUM; i++)
		{
			bull[i].x = 0;
			bull[i].y = 0;
			bull[i].live = false;

		}
		//�з��ӵ���ʼ��
		for (int i = 0; i < BULLET1_NUM+player.score/100; i++)
		{
			bull1[i].x = 0;
			bull1[i].y = 0;
			bull1[i].live = false;

		}
		//�л���ʼ��
		for (int i = 0; i < ENEMY_NUM+player.score/100; i++)
		{
			enemy[i].live = false;
			enemyHp(i);
		}
	}
	restarting = false;
}

void playerMove(int speed)
{


	//����ƶ�
#if 0
	//����Ƿ��м��̰��£����򷵻�ֵ�����򷵻ؼ�
	if (_kbhit())//<conio.h>���
	{
		//��һ�ַ�ʽ
	//_getch()  ������������scanfһ����û������ͻῨס������ȴ����룬����C���Եı�׼����
		char key = _getch();
		switch (key)
		{
		case 'w':
		case 'W':
			player.y -= speed/2;
			break;
		case 's':
		case 'S':
			player.y += speed/2;
			break;
		case 'a':
		case 'A':
			player.x -= speed/2;
			break;
		case 'd':
		case 'D':
			player.x += speed/2;
			break;
		}
	}
#elif 1
	//���õ�
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))//VK_UPϵͳ����ĺ�
	{
		if (player.y > 0)//�߽紦��
		{
			player.y -= speed;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if (player.y < HEIGHT - PLAN_HEIGHT)//��ֹ���߽�
		{
			player.y += speed;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		if (player.x  > 0)
		{
			player.x -= speed;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		if (player.x < WIDTH - PLAN_WIDTH)//��ֹ���߽�
		{
			player.x += speed;
		}
	}
#endif//0
}

void creatBullet()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (!bull[i].live)
		{
			bull[i].x = player.x + (PLAN_WIDTH / 2) - (BULLET_WIDTH / 2);
			bull[i].y = player.y;
			bull[i].live = true;
			break;//����
		}
	}
}

void creatBullet1()
{
	for (int i = 0; i < BULLET1_NUM; i++)
	{

		for (int i = 0; i < ENEMY_NUM + player.score / 100; i++)
		{
			if (!enemy[i].live)
			{
				continue;
			}
			if (enemy[i].type == SMALL)//ֻ��BIG�ɻ��ᷢ���ӵ�
			{
				continue;
			}
			for (int j = 0; j < BULLET1_NUM; j++)
			{
				if (bull1[j].live)
				{
					continue;
				}
				bull1[i].x = enemy[i].x + (enemy[i].width / 2) - (BULLET_WIDTH / 2);
				bull1[i].y = enemy[i].y + enemy[i].height;
				bull1[i].live = true;
				break;//����
			}
		}
	}
}
void bullet1Move(double speed)
{
	//�ӵ����Ƶ��
	if (Timer(2000, 4))//2000����
	{
		creatBullet1();
	}
	for (int i = 0; i < BULLET1_NUM; i++)
	{

		if (bull1[i].live)
		{
			bull1[i].y += speed+player.score/500.0;
			if (bull1[i].y > HEIGHT)//�����߽��ӵ��ж�����
			{
				bull1[i].live = false;
			}
		}
	}
}


	void bulletMove(int speed)
	{
		//�ӵ����Ƶ��
		if (GetAsyncKeyState(VK_SPACE) && Timer(200, 1))
		{
			creatBullet();
		}

		for (int i = 0; i < BULLET_NUM; i++)
		{

			if (bull[i].live)
			{
				bull[i].y -= speed;
				if (bull[i].y < 0)//�����߽��ӵ��ж�����
				{
					bull[i].live = false;
				}
			}
		}
	}

void enemyHp(int i)
{
	int flag = rand() % 100;
	if (flag >= 0 && flag <= 18)//�����deki�ɻ�
	{
		enemy[i].type = BIG;
		enemy[i].hp = BIG_PH;
		enemy[i].width = 104;
		enemy[i].height = 148;
	}
	else//С����deki�ɻ�
	{
		enemy[i].type = SMALL;
		enemy[i].hp = SMALL_PH;
		enemy[i].width = 52;
		enemy[i].height = 39;
	}
}

void creatEnemy()
{
	for (int i = 0; i < ENEMY_NUM+player.score/100; i++)
	{
		if (!enemy[i].live)
		{
			enemy[i].live = true;
			enemy[i].x = rand() % (WIDTH - (BIG_WIDTH + SMALL_WIDTH) / 2);
			enemy[i].y = 0;
			enemyHp(i);//���õл�HP
			break;
		}
	}
}

void enemyMove(double speed)
{
	for (int i = 0; i < ENEMY_NUM+player.score/100; i++)
	{
		if (enemy[i].live)
		{
			enemy[i].y += speed+player.score/1000.0;
			if (enemy[i].y > HEIGHT)
			{
				enemy[i].live = false;
			}
		}
	}
}

bool Timer(int time, int id)
{
	static DWORD t[10];
	if (clock() - t[id] > time)
	{
		t[id] = clock();
		return true;
	}
	return false;
}

void shootEnemy()//�з��ӵ�������ҷɻ�
{
		for (int i= 0; i < BULLET1_NUM; i++)
		{
			if (!bull1[i].live)
			{
				continue;
			}
			if (bull1[i].x+ BULLET1_WIDTH >player.x && bull1[i].x<player.x+ PLAN_WIDTH
				&& bull1[i].y+ BULLET1_HEIGHT>player.y && bull1[i].y<player.y+ 100)
			{//����Էɻ��ĸ߶��Լ�С29����β������Ϊ�Ҵ�����Ժ��������
				player.hp--;
				bull1[i].live = false;
				player.score--;
				if (player.hp <= 0 || player.score <= 0)
				{//�������ɻ��������˻�Է�����һ���жϣ����С��0��ô����״̬������ı䣬��Ϸ����
					isExpolde = true;
					AlreadyOver = true;
					player.live = false;
				}
			}
		}
}

void shootPlane()//�ҷ��ӵ����ео�
{
	for (int i = 0; i < ENEMY_NUM+player.score/100; i++)
	{
		if (!enemy[i].live)
		{
			continue;
		}
		for (int j = 0; j < BULLET_NUM; j++)
		{
			if (!bull[j].live)
			{
				continue;
			}
			if (bull[j].x+ BULLET_WIDTH > enemy[i].x && bull[j].x<enemy[i].x + enemy[i].width
				&& bull[j].y+ BULLET_HEIGHT>enemy[i].y && bull[j].y < enemy[i].y + enemy[i].height)//�ж��ӵ��Ƿ����
			{
				bull[j].live = false;
				enemy[i].hp--;
			}
		}
		if (enemy[i].hp <= 0)
		{

			if (enemy[i].type == BIG)
			{
				player.score += BIG_PH;
			}
			else
			{
				player.score += SMALL_PH;
			}
			enemy[i].live = false;

		}
	}
}

void Attacked()
{
	for (int i = 0; i < ENEMY_NUM+player.score/100; i++)
	{
		if (!enemy[i].live)
		{
			continue;
		}
		if (enemy[i].type == BIG)
		{//��л�����ײ�ж�
			if (player.x+ PLAN_WIDTH > enemy[i].x && player.x<enemy[i].x + enemy[i].width
				&& player.y+ PLAN_HEIGHT>enemy[i].y && player.y < enemy[i].y + enemy[i].height)
			{

				enemy[i].hp--;
				player.hp--;

				if (enemy[i].hp <= 0)
				{
					player.score += BIG_PH;
					enemy[i].live = false;
				}
				if (player.hp <= 0)
				{
					isExpolde = true;
					AlreadyOver = true;
					player.live = false;
				}

			}
		}
		if (enemy[i].type == SMALL)
		{//С�л�����ײ�ж�
			if (enemy[i].x + SMALL_WIDTH > player.x && enemy[i].x<player.x + player.width
				&& enemy[i].y>player.y && enemy[i].y < player.y + player.height - 20
				)//����player�ɻ�ͼ��β������
			{

				enemy[i].hp--;
				player.hp--;

				if (enemy[i].hp <= 0)
				{
					player.score += SMALL_PH;
					enemy[i].live = false;
				}
				if (player.hp <= 0)
				{
					isExpolde = true;
					AlreadyOver = true;
					player.live = false;
				}

			}
		}

	}
}



void textDraw()
{
	TCHAR hp[10];
	TCHAR sco[10];
	_stprintf(hp, _T("%d"), player.hp);
	_stprintf(sco, _T("%d"), player.score);

	settextstyle(20, 10, _T("����"));//��������
	settextcolor(BLACK);//������ɫ
	setbkmode(NULL);//������ֱ���
	outtextxy(0, 0, _T("PLAYER��ʽ�ض�"));
	//�÷�
	settextcolor(BLACK);
	outtextxy(0, 50, _T("�÷֣�"));
	settextcolor(GREEN);
	outtextxy(50, 50, sco);
	//hp
	settextcolor(BLACK);
	outtextxy(0, 25, _T("Ѫ����"));
	settextcolor(RED);
	outtextxy(50, 25, hp);

}
void BGMPLAY()
{
	// �������ļ�����������
	MCIERROR mciError;
	mciError = mciSendString(_T("open ./images/mushokutensei.mp3 alias BGM"), NULL, 0, NULL);
	if (mciError != 0) {
		// ���ļ�ʧ�ܣ����������Ϣ
		TCHAR errorMsg[128];
		mciGetErrorString(mciError, errorMsg, 128);
		MessageBox(NULL, errorMsg, _T("Error"), MB_OK);
		return;
	}

	mciError = mciSendString(_T("play BGM repeat"), NULL, 0, NULL);
	if (mciError != 0) {
		// ����ʧ�ܣ����������Ϣ
		TCHAR errorMsg[128];
		mciGetErrorString(mciError, errorMsg, 128);
		MessageBox(NULL, errorMsg, _T("Error"), MB_OK);
		return;
	}
}
//��ͣ����
void drawStopScreen()
{
	cleardevice();
	loadimage(&bk3, _T("./images/background3.jpg"));
	putimage(0, 0, &bk3);
	settextcolor(BLUE);
	settextstyle(30, 0, _T("����"));
	outtextxy(WIDTH / 2 - 170, HEIGHT / 2 - 30, _T("�� Esc ���ط���Ϸ"));
	FlushBatchDraw();
	cleardevice();
}

void drawStartScreen()
{
	putimage(0, 0, &bk1);
    settextcolor(YELLOW);
	settextstyle(25, 0, _T("����"));
	outtextxy(WIDTH / 2 - 130, HEIGHT / 2 - 30, _T("�� R ��ת���ɻ���ʼ��Ϸ"));
	outtextxy(10, HEIGHT / 2 + 200, _T("�ƶ�����"));
	putimage(10, HEIGHT / 2 + 250, &photo[0]);
	outtextxy(350, HEIGHT / 2 + 200, _T("�����ӵ�"));
	putimage(350 ,HEIGHT / 2 + 250, &photo[1]);
	outtextxy(30, 30, _T("��ҷɻ�"));
	putimage(30, 60, &img_role[0], NOTSRCERASE);
	putimage(30, 60, &img_role[1], SRCINVERT);
	outtextxy(260, 30, _T("�л�1��"));
	putimage(350, 30, &img_enemy[1][0], NOTSRCERASE);
	putimage(350, 30, &img_enemy[1][1], SRCINVERT);
	outtextxy(290, 70, _T("ײ������1��Ѫ��"));
	outtextxy(230, 100, _T("�л�2��"));
	putimage(310, 100, &img_enemy[0][0], NOTSRCERASE);
	putimage(310, 100, &img_enemy[0][1], SRCINVERT);
	outtextxy(290, 250, _T("ײ������3��Ѫ��"));
	outtextxy(260, 290, _T("�����ӵ�  ������"));
	putimage(363, 290, &img_bullet1[0], NOTSRCERASE);
	putimage(363, 290, &img_bullet1[1], SRCINVERT);
	outtextxy(260, 320, _T("�������1��Ѫ��"));
	settextstyle(15, 0, _T("����"));
	outtextxy(30, 250, _T("��ʼѪ��Ϊ15�����ٵ�0��Ϸ����"));
	outtextxy(30, 270, _T("���ּ��ٵ�0����Ϸ����"));
	outtextxy(30, 290, _T("��Ϸ�а�Esc����ͣ"));
	FlushBatchDraw();
	while (true) {
		if (GetAsyncKeyState('R') & 0x8000) {
			break;
		}
		Sleep(10); // �������ߣ���ֹ CPU ռ�ù���
	}
}
bool restartPressed;
void drawEndScreen()
{
	if (AlreadyOver)
	{
		bool restartPressed = false;
		cleardevice();
		loadimage(&bk2, _T("./images/background2.jpg"));
		putimage(0, 0, &bk2);
		settextcolor(WHITE);
		settextstyle(30, 0, _T("����"));
		TCHAR s[20];
		_stprintf(s, _T("��Ϸ�������÷֣�%d"), player.score);
		outtextxy(WIDTH / 2 - 100, HEIGHT / 2 - 200, s);
		outtextxy(WIDTH / 2 - 100, HEIGHT / 2 - 160, _T("�� R �����¿�ʼ��Ϸ"));
		FlushBatchDraw();

		while (!restartPressed)
		{
			if (GetAsyncKeyState('R') & 0x8000)
			{
				AlreadyOver = false;
				restartPressed = true;
				restarting = true;
				isExpolde = false;
			}
			Sleep(10);
		}

		// �����ʾ���ݣ�׼�����¿�ʼ��Ϸ
		cleardevice();
	}
}


