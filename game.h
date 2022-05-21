#pragma once
#include <conio.h>
#include <windows.h>  
#include <iostream>
#include <time.h>

#include "snake.h"
#include "colormap.h"

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

#define _N 15

class Game{
	Snake s;//创建一条蛇 
	Food f;//创建一个食物对象 
	Map m; //创建一张地图 

	clock_t c_1,c_2; //时间标志 
	int goal;//键盘点击的方向 
	//游戏初始化 
	void Init()
	{
		system("cls");
		s.Init(1,_N-1);
		f.New(1,1,_N-1,_N-1,s);
		goal = s.goal;
	}
	
public:
	Game(){
		c_1 = c_2 = clock();//获取当前时间 
		goal = 0; //默认初始方向为上 
	}

	void gotoxy(int x,int y){m.gotoxy(x,y);}
	//菜单 
	void Menu(int choose=0)
	{	
	
		m.gotoxy(0,0);
		
	    CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int Y = csbi.dwCursorPosition.Y;		
		
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_GREEN); //设置字体颜色为绿色 
		std::cout<<"\t\t\t┌──────────────────────────────────────┐\n";
		std::cout<<"\t\t\t│                                      │\n";
		std::cout<<"\t\t\t├──────────────────────────────────────┤\n";
		std::cout<<"\t\t\t│                                      │\n"; 
		std::cout<<"\t\t\t│                                      │\n"; 
		std::cout<<"\t\t\t│                                      │\n";
		std::cout<<"\t\t\t│                                      │\n";
		std::cout<<"\t\t\t│                                      │\n";
		std::cout<<"\t\t\t│                                      │\n";
		std::cout<<"\t\t\t│                                      │\n";
		std::cout<<"\t\t\t└──────────────────────────────────────┘\n";
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //白色字体
		m.gotoxy(38,1 + Y);		std::cout<<"炫 彩 贪 吃 蛇 ";
		m.gotoxy(35,8 + Y);	std::cout<<" 3 / Esc    退出游戏 "; 
	
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED); //红色 
		m.gotoxy(35,4 + Y);	std::cout<<" 1 / Enter  开始游戏 "; 

		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED); //黄色 
		m.gotoxy(35,6 + Y);	std::cout<<" 2 / Space  游戏说明 "; 
		
		
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_BLUE); //蓝色
		//限制选择按钮 
		switch(choose)
		{
			case 0:	m.gotoxy(30 ,4 + Y);	std::cout<<" ->";	break; 	//开始游戏 
			case 1:	m.gotoxy(30 ,6 + Y);	std::cout<<" ->";	break; 	//游戏说明 
			case 2:	m.gotoxy(30 ,8 + Y);	std::cout<<" ->";	break; 	//退出游戏 
		}
		
		m.gotoxy(0,11 + Y); //光标走到正常位置 
	} 
	//帮助 
	void Help()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int Y = csbi.dwCursorPosition.Y;		
	
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_GREEN); //设置字体颜色为绿色 
		std::cout<<"\t\t\t┌──────────────────────────────────────┐\n";	//0 
		std::cout<<"\t\t\t│                                      │\n";
		std::cout<<"\t\t\t├──────────────────────────────────────┤\n";	//2 
		std::cout<<"\t\t\t│                                      │\n"; 
		std::cout<<"\t\t\t│                                      │\n";	//4 
		std::cout<<"\t\t\t│           上:W  左:A  下:S  右:D     │\n";
		std::cout<<"\t\t\t│                                      │\n";	//6 
		std::cout<<"\t\t\t│                                      │\n";
		std::cout<<"\t\t\t│           本游戏由散人玩家制作，游   │\n";	//8 
		std::cout<<"\t\t\t│       戏可随意修改，仅供学习。       │\n";
		std::cout<<"\t\t\t│                                      │\n";	//10 
		std::cout<<"\t\t\t│  ┌───────────────────────────────┐   │\n"; 
		std::cout<<"\t\t\t│  │ 作者 ：学习懒惰               │   │\n";	//12 
		std::cout<<"\t\t\t│  ├───────────────────────────────┤   │\n"; 
		std::cout<<"\t\t\t│  │ 邮箱 ：2700768668@qq.com      │   │\n";	//14
		std::cout<<"\t\t\t│  └───────────────────────────────┘   │\n"; 
		std::cout<<"\t\t\t└──────────────────────────────────────┘\n";	//16
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //白色字体
		m.gotoxy(40,1 + Y);		std::cout<<"说  明  书  ";
		
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED); //红色
		m.gotoxy(26,4 + Y);	std::cout<<"  操作说明: ";
		m.gotoxy(26,7 + Y);	std::cout<<"  游戏简介: ";
		m.gotoxy(35,17+ Y);
	} 
	//开始游戏 
	void Play()
	{
		Init();
		int c_0,move;
		while(1)
		{
			c_0 = clock();

			if	(( KEY_DOWN(VK_SPACE))) getch(); //空格暂停 
			else if	(( KEY_DOWN('W') || KEY_DOWN(VK_UP)   ) && s.goal!=2)	goal = 0; //上 
			else if	(( KEY_DOWN('A') || KEY_DOWN(VK_LEFT) ) && s.goal!=3) 	goal = 1; //左 
			else if	(( KEY_DOWN('S') || KEY_DOWN(VK_DOWN) ) && s.goal!=0) 	goal = 2; //下 
			else if	(( KEY_DOWN('D') || KEY_DOWN(VK_RIGHT)) && s.goal!=1) 	goal = 3; //右

			//移动间隔
			if(c_0 - c_2 > 200)
			{
				c_1 = c_2; //移动完了必定刷新屏幕 
				c_2 = c_0;
				s.goal = goal; //将键盘点击的方向赋值给蛇的方向 
				move = s.Move(f.Getx(),f.Gety(),1,1,_N-1,_N-1); //移动 
				
				if(move == 2) //食物被吃了
				{
					f.New(1,1,_N-1,_N-1,s);
				}
				else if(move == 0) //撞死了 
				{
					m.over(s,_N); //播放game over 动画
					m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED); //红色
					std::cout<<"\n\t\t\t    GAME OVER! 敲回车继续~";	//打印死亡提示 
					while(getch()!=13); //吃掉控制台缓存 
					return; //退出Game.play() 
				}
			}
			
			//刷屏间隔 
			if (c_0 - c_1 > 99)
			{
				c_1 = c_0;
				m.Show(f,s,_N);
			}

		}
	};
};
