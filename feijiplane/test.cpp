#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
double speed1;
int main()
{
	//创建一个图形窗口
	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);//SHOWCONSOLE  在输出图形函数的同时，把printf函数窗口也显示出来，方便对比界面看数据
	loadImg();
	drawStartScreen();//最初始的界面，按R进入游戏
	BGMPLAY();

	//双缓冲绘图
	BeginBatchDraw();
	bool isPaused = false;
	double speed1 = 1.0;
	while (1)//游戏循环主体
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)//ESC暂停
		{
			isPaused = !isPaused;
			Sleep(200); // 防止重复按键
		}
		if (!isPaused)
		{
			    gameInit();
				//
				textDraw();
				FlushBatchDraw();
				playerMove(PLAYER_SPEED);
				bulletMove(BULLET_SPEED);
				bullet1Move(0.3);

				if (Timer(500, 0))
				{
					creatEnemy();
				}

				if (Timer(50, 2))
				{
					enemyMove(speed1);
				}
				if (Timer(30000, 3))
				{
					speed1 = speed1 + 0.05;
				}
				shootPlane();
				shootEnemy();
				Attacked();	
				gameDraw();
                // 判断是否绘制结束界面
				drawEndScreen();
		}
		else//暂停界面
		{
			drawStopScreen();
			Sleep(100);
		}
	}
	EndBatchDraw();

	return 0;
}