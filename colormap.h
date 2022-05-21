#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "snake.h"
#include "food.h"

#define maxn 20

class Map{
	int map[maxn][maxn];
	
	HANDLE hOutput; //控制台缓冲区
	
	CONSOLE_CURSOR_INFO cci; //光标的属性 
	DWORD bytes;
	
	char data[8000]; //缓冲区 
	
	/*初始化空地图数组*/ 
	void Init(int n)
	{
		int i,j;
		for(i=0;i < n;i++)
		{
			for(j=0;j < n;j++)
			{
				if(i == 0 || i==n-1) map[j][i] = 1; //墙壁的标志
				else if(j == 0 || j==n-1) map[j][i] = 1; //墙壁的标志
				else map[j][i] = 0; //没有东西
			}
		}
	} 
	/*打印列表*/
	void Out(int n)
	{	
		static bool flag=0; //食物闪烁标记 
		int i,j;
	
		gotoxy(0,0);
		for(j=0;j<n;j++)
		{
			std::cout<<std::endl<<"\t\t\t ";
			for(i=0;i<n;i++)
			{
				switch(map[j][i])
				{
					case 0:	std::cout<<"   ";	break; //没有东西
					case 1: 
							setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //白色字体
							std::cout<<"[+]"; 	break; //墙壁 
					case 2: 
							setcolor(FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN); //蓝色+绿色字体 
							std::cout<<(flag?"*+*":" * ");
							flag=!flag; 		break; //食物
					case 3: 
							setcolor(FOREGROUND_INTENSITY|FOREGROUND_GREEN);//绿色字体 
							std::cout<<"(O)"; 	break; //蛇身
					case 4: 
							setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED);//红色字体 
							std::cout<<"(X)"; 	break; //蛇头
					case 5: 
							setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED);//红色字体 
							std::cout<<" * "; 	break; //待删除
				}
			}
		}
	} 
	
public:
	//c++版gotoxy函数 
	void gotoxy(int x,int y)                
	{
		COORD c={x,y};
		SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE),c);
	}
	//c++版setcolor函数    
	void setcolor(WORD wAttributes)                
	{
		SetConsoleTextAttribute(hOutput, wAttributes);

//		wAttributes			    颜色			对应的值
//		
//		FOREGROUND_BLUE			字体颜色：蓝 		1
//		FOREGROUND_GREEN 		字体颜色：绿 		2
//		FOREGROUND_RED 			字体颜色：红 		4
//		FOREGROUND_INTENSITY 	前景色高亮显示 		8
//		BACKGROUND_BLUE 		背景颜色：蓝  		16
//		BACKGROUND_GREEN 		背景颜色：绿 		32
//		BACKGROUND_RED 			背景颜色：红 		64
//		BACKGROUND_INTENSITY 	背景色高亮显示 		128
	}
	Map(){
	
		system("color 0A");
	    //获取默认标准显示缓冲区句柄
	    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	 
	    //隐藏缓冲区的光标
	    cci.bVisible = 0;
	    cci.dwSize = 1;
	    SetConsoleCursorInfo(hOutput, &cci);
	}
	void Show(Food f,Snake s,int n)//n代表地图的宽度 
	{
		
		Body *p;
		
		//初始化空地图数组
		Init(n);
		
		//将食物坐标添加到地图数组 
		map[f.Gety()][f.Getx()] = 2; //食物标志
		
		//将身体的坐标添加到地图数组 s
		for(p=s.Get()->next; p->next!=NULL; p = p->next)
		{
			map[p->y][p->x] = 3; //蛇身体的标志
		}
		//将蛇头添加到地图数组 
		map[p->y][p->x] = 4;// 蛇头的标志

		//打印地图
		Out(n);
		//打印成绩
		std::cout<<"\n\n\t\t\t\t 得分："<<s.lenth()-3; 
	}
	void over(Snake s,int n)
	{
		Body *p,*pre;
		int time = s.lenth()>10 ? 100:200-s.lenth()*10; 
		while(s.Get()->next)
		{	
			//初始化空地图数组
			Init(n);
		
			//将身体的坐标添加到地图数组 s
			for(pre=s.Get(),p=pre->next; p->next!=NULL; p=p->next)
			{
				pre = p;
				map[p->y][p->x] = 3; //蛇身体的标志
			}
					
			//将蛇头添加到地图数组
			map[p->y][p->x] = 5; //蛇头待删除的标志
			
			//打印地图 
			Out(n);	
			//打印得分	
			std::cout<<"\n\n\t\t\t\t 得分："<<s.lenth()-3; 
			
			//删除蛇头 
			pre->next = NULL;
			delete(p);
			Sleep(time);
		}
	}
	
};

