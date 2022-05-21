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
	Body *first;//蛇尾 
	Body *last; //蛇头 
	Body *lastPre;//蛇头的前一个位置
	int len;//记录蛇的长度 
	 
	/*删除当前蛇的数据*/
	void del();
public:
	int goal;//方向 0上，1左，2下，3右 
	
	Snake();
	void Init(int ,int );/*初始化蛇的数据 */ 
	int lenth(){return len;}/*获得蛇的长度*/ 
	 Body *Get(){return first;}/*获得蛇*/
	int Move(int, int, int, int, int, int);/*蛇移动一下*/

};


Snake::Snake(){
	srand((unsigned int)(time(NULL))); //初始化时间种子
	
	first	= new Body;//头节点
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
	del(); //删除蛇之前的数据 		
	len = 2;//初始化蛇长2
	
	int c2 = (max+min)/2;
	int d2 = (max-min)/2;

	int X = rand()%d2 - d2/2 + c2;
	int Y = rand()%d2 - d2/2 + c2;
	
	lastPre = new Body(first,X,Y);//在first后新建一个节点，数据为(X,Y) 
	last 	= new Body(lastPre); //在lastPre后新建一个节点
	
	goal = rand()%4; //随机初始化方向
	
	switch(goal)
	{
		case 0: last->x = lastPre->x;		last->y = lastPre->y-1;		break;//上 
		case 1: last->x = lastPre->x-1;		last->y = lastPre->y;		break;//左 
		case 2: last->x = lastPre->x;		last->y = lastPre->y+1;		break;//下
		case 3: last->x = lastPre->x+1;		last->y = lastPre->y;		break;//右 
	}
} 
int Snake::Move(int food_x,int food_y,int x1,int y1,int x2,int y2){
	Body *p,*s=new(Body);
	
	switch(goal)
	{
		case 0: s->x = last->x;		s->y = last->y-1;	break;//上 
		case 1: s->x = last->x-1;	s->y = last->y;		break;//左 
		case 2: s->x = last->x;		s->y = last->y+1;	break;//下 
		case 3: s->x = last->x+1;	s->y = last->y;		break;//右 
	}
	/*判断是否会碰到身体*/ 
	for(p=first->next->next; p!=NULL; p=p->next)
	{
		if(p->x == s->x && p->y == s->y)
		{
			return 0;
		}
	}
	
	/*判断是否碰到墙壁*/
	if(s->x < x1 || s->x >= x2 || s->y < y1 || s->y >= y2) return 0;
	
	/*头部添加一节*/ 
	last->next = s;
	lastPre = last;
	last = last->next;
	last->next = 0;

	/*判断是否吃到食物*/
	if(s->x == food_x && s->y == food_y) 
	{
		len++; //蛇长加一 
		return 2;//返回吃到食物标记2 
	}
	
	/*尾部删除一节*/
	p = first->next;
	first->next = p->next;
	delete(p);
 
	/*无特殊情况正常移动返回1*/ 
	return 1; 
} 
