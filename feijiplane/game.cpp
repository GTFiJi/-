#define _CRT_SECURE_NO_WARNINGS

#include "game.h"
#include "graphics.h"


//把图片加载进程序
IMAGE bk;//背景图片
IMAGE bk1;
IMAGE bk2;
IMAGE bk3;
IMAGE photo[2];//初始界面键图片
IMAGE img_role[2];//玩家图片
IMAGE img_bullet[2];//子弹图片
IMAGE img_bullet1[2];//敌方子弹图片
IMAGE img_enemy[2][2];//敌机图片
IMAGE imgdieplane[2];//玩家飞机死亡图片


void loadImg()
{
	//加载背景图片 480 * 852
	loadimage(&bk, _T("./images/background.jpg"));	loadimage(&bk1, _T("./images/background1.jpg"));
	//加载初始界面图片
	loadimage(&photo[0], _T("./images/R.jpg"));
	loadimage(&photo[1], _T("./images/space.jpg"));
	//loadimage(&bk1, _T("./images/background1.jpg"));//单独加载

	//加载敌机的图片
	//大
	loadimage(&img_enemy[0][0], _T("./images/enemyda1.jpg"));//掩码图
	loadimage(&img_enemy[0][1], _T("./images/enemyda.jpg"));//原图
	//小
	loadimage(&img_enemy[1][0], _T("./images/enemy_1.jpg"));//掩码图
	loadimage(&img_enemy[1][1], _T("./images/enemy_2.jpg"));//原图

	//加载玩家图片
	loadimage(&img_role[0], _T("./images/hero2.jpg"));//掩码图不会搞就放一张好了
	loadimage(&img_role[1], _T("./images/hero1.jpg"));//原图

	//加载玩家子弹图片
	loadimage(&img_bullet[0], _T("./images/bullet2.jpg"));//掩码图
	loadimage(&img_bullet[1], _T("./images/bullet1.jpg"));//原图

	//加载敌方子弹图片
	loadimage(&img_bullet1[0], _T("./images/bullet11.jpg"));//掩码图
	loadimage(&img_bullet1[1], _T("./images/bullet12.jpg"));//原图
	//飞机爆炸图片
	loadimage(&imgdieplane[0], _T("./images/planeExplode1.jpg"));//掩码图
	loadimage(&imgdieplane[1], _T("./images/planeExplode2.jpg"));//原图

}
struct plane//玩家飞机与敌机
{
	int x;//x坐标
	int y;//y坐标
	bool live;//是否存活
	int width;//宽度
	int height;//高度
	int hp;//血量
	int type;//敌机类型 big small
	int score;//得分
}player, enemy[1000];

struct bullet//我方子弹
{
	int x;
	int y;
	bool live;//是否存活
}bull[BULLET_NUM];

struct bullet1//敌军子弹
{
	double x;
	double y;
	bool live;
}bull1[BULLET1_NUM];

bool isExpolde = false; // 飞机是否爆炸
bool AlreadyOver = false;

void gameDraw()
{

	//把背景图沾到窗口上
	putimage(0, 0, &bk);

	//绘制玩家飞机 
	//透明贴图技术：用掩码图和原图做一个颜色的二进制操作
	if (!isExpolde)
	{
		//玩家飞机没有爆炸，还有hp
		putimage(player.x, player.y, &img_role[0], NOTSRCERASE);
		putimage(player.x, player.y, &img_role[1], SRCINVERT);
	}
	else
	{
		//玩家飞机无hp了爆炸了
		putimage(player.x, player.y, &imgdieplane[0], NOTSRCERASE);
		putimage(player.x, player.y, &imgdieplane[1], SRCINVERT);
		Sleep(2000);//游戏结束
	}

	//绘制我方子弹
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bull[i].live)
		{
			putimage(bull[i].x, bull[i].y, &img_bullet[0], NOTSRCERASE);
			putimage(bull[i].x, bull[i].y, &img_bullet[1], SRCINVERT);
		}
	}
	//绘制敌方子弹
	for (int i = 0; i < BULLET1_NUM; i++)
	{
		if (bull1[i].live)
		{
			putimage(bull1[i].x, bull1[i].y, &img_bullet1[0], NOTSRCERASE);
			putimage(bull1[i].x, bull1[i].y, &img_bullet1[1], SRCINVERT);
		}
	}

	//绘制敌机
	for (int i = 0; i < ENEMY_NUM+player.score; i++)
	{
		if (enemy[i].live)
		{
			if (enemy[i].type == BIG)
			{
				//大飞机贴图
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][1], SRCINVERT);
			}
			else
			{
				//小飞机贴图
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][1], SRCINVERT);
			}
		}
	}
}
bool restarting = true;
void gameInit()
{
	if (restarting)//restarting作为判断是否初始
	{

		//玩家初始化
		player.x = WIDTH / 2- PLAN_WIDTH/2;
		player.y = HEIGHT - PLAN_HEIGHT;
		player.live = true;
		player.hp = 15;
		player.score = 0;
		player.height = PLAN_HEIGHT;
		player.width = PLAN_WIDTH;

		//我方子弹初始化
		for (int i = 0; i < BULLET_NUM; i++)
		{
			bull[i].x = 0;
			bull[i].y = 0;
			bull[i].live = false;

		}
		//敌方子弹初始化
		for (int i = 0; i < BULLET1_NUM+player.score/100; i++)
		{
			bull1[i].x = 0;
			bull1[i].y = 0;
			bull1[i].live = false;

		}
		//敌机初始化
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


	//玩家移动
#if 0
	//检测是否有键盘按下，有则返回值，否则返回假
	if (_kbhit())//<conio.h>里的
	{
		//第一种方式
	//_getch()  阻塞函数，和scanf一样，没有输入就会卡住主程序等待输入，不是C语言的标准函数
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
	//采用的
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))//VK_UP系统定义的宏
	{
		if (player.y > 0)//边界处理
		{
			player.y -= speed;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if (player.y < HEIGHT - PLAN_HEIGHT)//防止出边界
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
		if (player.x < WIDTH - PLAN_WIDTH)//防止出边界
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
			break;//跳出
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
			if (enemy[i].type == SMALL)//只有BIG飞机会发射子弹
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
				break;//跳出
			}
		}
	}
}
void bullet1Move(double speed)
{
	//子弹射击频率
	if (Timer(2000, 4))//2000毫秒
	{
		creatBullet1();
	}
	for (int i = 0; i < BULLET1_NUM; i++)
	{

		if (bull1[i].live)
		{
			bull1[i].y += speed+player.score/500.0;
			if (bull1[i].y > HEIGHT)//超出边界子弹判断死亡
			{
				bull1[i].live = false;
			}
		}
	}
}


	void bulletMove(int speed)
	{
		//子弹射击频率
		if (GetAsyncKeyState(VK_SPACE) && Timer(200, 1))
		{
			creatBullet();
		}

		for (int i = 0; i < BULLET_NUM; i++)
		{

			if (bull[i].live)
			{
				bull[i].y -= speed;
				if (bull[i].y < 0)//超出边界子弹判定死亡
				{
					bull[i].live = false;
				}
			}
		}
	}

void enemyHp(int i)
{
	int flag = rand() % 100;
	if (flag >= 0 && flag <= 18)//大敌人deki飞机
	{
		enemy[i].type = BIG;
		enemy[i].hp = BIG_PH;
		enemy[i].width = 104;
		enemy[i].height = 148;
	}
	else//小敌人deki飞机
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
			enemyHp(i);//重置敌机HP
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

void shootEnemy()//敌方子弹击中玩家飞机
{
		for (int i= 0; i < BULLET1_NUM; i++)
		{
			if (!bull1[i].live)
			{
				continue;
			}
			if (bull1[i].x+ BULLET1_WIDTH >player.x && bull1[i].x<player.x+ PLAN_WIDTH
				&& bull1[i].y+ BULLET1_HEIGHT>player.y && bull1[i].y<player.y+ 100)
			{//这里对飞机的高度略减小29，即尾部，因为我打算忽略后面的喷气
				player.hp--;
				bull1[i].live = false;
				player.score--;
				if (player.hp <= 0 || player.score <= 0)
				{//如果这里飞机被击中了会对分数有一个判断，如果小于0那么几个状态参数便改变，游戏结束
					isExpolde = true;
					AlreadyOver = true;
					player.live = false;
				}
			}
		}
}

void shootPlane()//我方子弹击中敌军
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
				&& bull[j].y+ BULLET_HEIGHT>enemy[i].y && bull[j].y < enemy[i].y + enemy[i].height)//判定子弹是否击中
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
		{//大敌机的碰撞判断
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
		{//小敌机的碰撞判断
			if (enemy[i].x + SMALL_WIDTH > player.x && enemy[i].x<player.x + player.width
				&& enemy[i].y>player.y && enemy[i].y < player.y + player.height - 20
				)//考虑player飞机图像尾部喷气
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

	settextstyle(20, 10, _T("宋体"));//设置字体
	settextcolor(BLACK);//设置颜色
	setbkmode(NULL);//清空文字背景
	outtextxy(0, 0, _T("PLAYER：式守都"));
	//得分
	settextcolor(BLACK);
	outtextxy(0, 50, _T("得分："));
	settextcolor(GREEN);
	outtextxy(50, 50, sco);
	//hp
	settextcolor(BLACK);
	outtextxy(0, 25, _T("血量："));
	settextcolor(RED);
	outtextxy(50, 25, hp);

}
void BGMPLAY()
{
	// 打开音乐文件并播放音乐
	MCIERROR mciError;
	mciError = mciSendString(_T("open ./images/mushokutensei.mp3 alias BGM"), NULL, 0, NULL);
	if (mciError != 0) {
		// 打开文件失败，输出错误信息
		TCHAR errorMsg[128];
		mciGetErrorString(mciError, errorMsg, 128);
		MessageBox(NULL, errorMsg, _T("Error"), MB_OK);
		return;
	}

	mciError = mciSendString(_T("play BGM repeat"), NULL, 0, NULL);
	if (mciError != 0) {
		// 播放失败，输出错误信息
		TCHAR errorMsg[128];
		mciGetErrorString(mciError, errorMsg, 128);
		MessageBox(NULL, errorMsg, _T("Error"), MB_OK);
		return;
	}
}
//暂停界面
void drawStopScreen()
{
	cleardevice();
	loadimage(&bk3, _T("./images/background3.jpg"));
	putimage(0, 0, &bk3);
	settextcolor(BLUE);
	settextstyle(30, 0, _T("宋体"));
	outtextxy(WIDTH / 2 - 170, HEIGHT / 2 - 30, _T("按 Esc 键重返游戏"));
	FlushBatchDraw();
	cleardevice();
}

void drawStartScreen()
{
	putimage(0, 0, &bk1);
    settextcolor(YELLOW);
	settextstyle(25, 0, _T("宋体"));
	outtextxy(WIDTH / 2 - 130, HEIGHT / 2 - 30, _T("按 R 键转生飞机开始游戏"));
	outtextxy(10, HEIGHT / 2 + 200, _T("移动控制"));
	putimage(10, HEIGHT / 2 + 250, &photo[0]);
	outtextxy(350, HEIGHT / 2 + 200, _T("发射子弹"));
	putimage(350 ,HEIGHT / 2 + 250, &photo[1]);
	outtextxy(30, 30, _T("玩家飞机"));
	putimage(30, 60, &img_role[0], NOTSRCERASE);
	putimage(30, 60, &img_role[1], SRCINVERT);
	outtextxy(260, 30, _T("敌机1："));
	putimage(350, 30, &img_enemy[1][0], NOTSRCERASE);
	putimage(350, 30, &img_enemy[1][1], SRCINVERT);
	outtextxy(290, 70, _T("撞击减少1点血量"));
	outtextxy(230, 100, _T("敌机2："));
	putimage(310, 100, &img_enemy[0][0], NOTSRCERASE);
	putimage(310, 100, &img_enemy[0][1], SRCINVERT);
	outtextxy(290, 250, _T("撞击减少3点血量"));
	outtextxy(260, 290, _T("发射子弹  并击中"));
	putimage(363, 290, &img_bullet1[0], NOTSRCERASE);
	putimage(363, 290, &img_bullet1[1], SRCINVERT);
	outtextxy(260, 320, _T("减少玩家1点血量"));
	settextstyle(15, 0, _T("宋体"));
	outtextxy(30, 250, _T("初始血量为15，减少到0游戏结束"));
	outtextxy(30, 270, _T("积分减少到0，游戏结束"));
	outtextxy(30, 290, _T("游戏中按Esc键暂停"));
	FlushBatchDraw();
	while (true) {
		if (GetAsyncKeyState('R') & 0x8000) {
			break;
		}
		Sleep(10); // 短暂休眠，防止 CPU 占用过高
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
		settextstyle(30, 0, _T("宋体"));
		TCHAR s[20];
		_stprintf(s, _T("游戏结束，得分：%d"), player.score);
		outtextxy(WIDTH / 2 - 100, HEIGHT / 2 - 200, s);
		outtextxy(WIDTH / 2 - 100, HEIGHT / 2 - 160, _T("按 R 键重新开始游戏"));
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

		// 清除显示内容，准备重新开始游戏
		cleardevice();
	}
}


