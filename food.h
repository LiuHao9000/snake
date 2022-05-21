#pragma once
#include <iostream>
#include <time.h> 
#include <stdlib.h>
#include "snake.h"

class Food{
	int x,y;
public:
	/*ʳ���ʼ��*/
	Food()
	{
		srand((unsigned int)(time(NULL))); //��ʼ��ʱ������
	}
	/*�½�ʳ��*/ 
	void New(int x1,int y1,int x2,int y2,Snake s)//���ɵķ�Χ�����Ͻ�����(x1,y1)~���½�����(x2,y2) 
	{
		Body *p = s.Get()->next;
		
		while(p!=NULL)
		{
			x=rand()%(x2-x1-1) + x1 + 1; 
			y=rand()%(y2-y1-1) + y1 + 1;
			
			/*�������ɵ�ʳ�����ߵ�������*/
			for(p=s.Get()->next; p!=NULL; p=p->next)
			{
				if(p->x == x  && p->y == y)
				{
					break;
				}
			}
		}
	}
	/*���ʳ���x����*/ 
	int Getx(){return x;}
	/*���ʳ���y����*/
	int Gety(){return y;}
};

