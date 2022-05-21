#pragma once
#include <iostream>
#include <time.h> 
#include <stdlib.h>
#include "snake.h"

class Food{
	int x,y;
public:
	/*食物初始化*/
	Food()
	{
		srand((unsigned int)(time(NULL))); //初始化时间种子
	}
	/*新建食物*/ 
	void New(int x1,int y1,int x2,int y2,Snake s)//生成的范围，左上角坐标(x1,y1)~右下角坐标(x2,y2) 
	{
		Body *p = s.Get()->next;
		
		while(p!=NULL)
		{
			x=rand()%(x2-x1-1) + x1 + 1; 
			y=rand()%(y2-y1-1) + y1 + 1;
			
			/*避免生成的食物在蛇的身体上*/
			for(p=s.Get()->next; p!=NULL; p=p->next)
			{
				if(p->x == x  && p->y == y)
				{
					break;
				}
			}
		}
	}
	/*获得食物的x坐标*/ 
	int Getx(){return x;}
	/*获得食物的y坐标*/
	int Gety(){return y;}
};

