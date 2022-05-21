#pragma once
#include <conio.h>
#include <time.h> 
#include <stdlib.h>

class Body{
public:
	int x,y;
	Body *next;
	
	Body(int X=0,int Y=0):x(X),y(Y){next = NULL;}
	
	Body(Body *pre,int X=0,int Y=0):x(X),y(Y){
		next = NULL;
		pre->next = this;
	}
};

class Snake{
	Body *first;//��β 
	Body *last; //��ͷ 
	Body *lastPre;//��ͷ��ǰһ��λ��
	int len;//��¼�ߵĳ��� 
	 
	/*ɾ����ǰ�ߵ�����*/
	void del();
public:
	int goal;//���� 0�ϣ�1��2�£�3�� 
	
	Snake();
	void Init(int ,int );/*��ʼ���ߵ����� */ 
	int lenth(){return len;}/*����ߵĳ���*/ 
	 Body *Get(){return first;}/*�����*/
	int Move(int, int, int, int, int, int);/*���ƶ�һ��*/

};


Snake::Snake(){
	srand((unsigned int)(time(NULL))); //��ʼ��ʱ������
	
	first	= new Body;//ͷ�ڵ�
	lastPre = NULL;
	last = NULL;
	len = 0;
}

void Snake::del(){
	lastPre = NULL;
	last = NULL;
	len = 0;

	Body *p=first->next;		
	while(p!=NULL)
	{
		first->next = p->next;
		free(p);
		p = first->next;
	}
}

void Snake::Init(int min,int max){
	del(); //ɾ����֮ǰ������ 		
	len = 2;//��ʼ���߳�2
	
	int c2 = (max+min)/2;
	int d2 = (max-min)/2;

	int X = rand()%d2 - d2/2 + c2;
	int Y = rand()%d2 - d2/2 + c2;
	
	lastPre = new Body(first,X,Y);//��first���½�һ���ڵ㣬����Ϊ(X,Y) 
	last 	= new Body(lastPre); //��lastPre���½�һ���ڵ�
	
	goal = rand()%4; //�����ʼ������
	
	switch(goal)
	{
		case 0: last->x = lastPre->x;		last->y = lastPre->y-1;		break;//�� 
		case 1: last->x = lastPre->x-1;		last->y = lastPre->y;		break;//�� 
		case 2: last->x = lastPre->x;		last->y = lastPre->y+1;		break;//��
		case 3: last->x = lastPre->x+1;		last->y = lastPre->y;		break;//�� 
	}
} 
int Snake::Move(int food_x,int food_y,int x1,int y1,int x2,int y2){
	Body *p,*s=new(Body);
	
	switch(goal)
	{
		case 0: s->x = last->x;		s->y = last->y-1;	break;//�� 
		case 1: s->x = last->x-1;	s->y = last->y;		break;//�� 
		case 2: s->x = last->x;		s->y = last->y+1;	break;//�� 
		case 3: s->x = last->x+1;	s->y = last->y;		break;//�� 
	}
	/*�ж��Ƿ����������*/ 
	for(p=first->next->next; p!=NULL; p=p->next)
	{
		if(p->x == s->x && p->y == s->y)
		{
			return 0;
		}
	}
	
	/*�ж��Ƿ�����ǽ��*/
	if(s->x < x1 || s->x >= x2 || s->y < y1 || s->y >= y2) return 0;
	
	/*ͷ�����һ��*/ 
	last->next = s;
	lastPre = last;
	last = last->next;
	last->next = 0;

	/*�ж��Ƿ�Ե�ʳ��*/
	if(s->x == food_x && s->y == food_y) 
	{
		len++; //�߳���һ 
		return 2;//���سԵ�ʳ����2 
	}
	
	/*β��ɾ��һ��*/
	p = first->next;
	first->next = p->next;
	delete(p);
 
	/*��������������ƶ�����1*/ 
	return 1; 
} 
