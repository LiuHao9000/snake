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
	Snake s;//����һ���� 
	Food f;//����һ��ʳ����� 
	Map m; //����һ�ŵ�ͼ 

	clock_t c_1,c_2; //ʱ���־ 
	int goal;//���̵���ķ��� 
	//��Ϸ��ʼ�� 
	void Init()
	{
		system("cls");
		s.Init(1,_N-1);
		f.New(1,1,_N-1,_N-1,s);
		goal = s.goal;
	}
	
public:
	Game(){
		c_1 = c_2 = clock();//��ȡ��ǰʱ�� 
		goal = 0; //Ĭ�ϳ�ʼ����Ϊ�� 
	}

	void gotoxy(int x,int y){m.gotoxy(x,y);}
	//�˵� 
	void Menu(int choose=0)
	{	
	
		m.gotoxy(0,0);
		
	    CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int Y = csbi.dwCursorPosition.Y;		
		
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_GREEN); //����������ɫΪ��ɫ 
		std::cout<<"\t\t\t��������������������������������������������������������������������������������\n";
		std::cout<<"\t\t\t��                                      ��\n";
		std::cout<<"\t\t\t��������������������������������������������������������������������������������\n";
		std::cout<<"\t\t\t��                                      ��\n"; 
		std::cout<<"\t\t\t��                                      ��\n"; 
		std::cout<<"\t\t\t��                                      ��\n";
		std::cout<<"\t\t\t��                                      ��\n";
		std::cout<<"\t\t\t��                                      ��\n";
		std::cout<<"\t\t\t��                                      ��\n";
		std::cout<<"\t\t\t��                                      ��\n";
		std::cout<<"\t\t\t��������������������������������������������������������������������������������\n";
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //��ɫ����
		m.gotoxy(38,1 + Y);		std::cout<<"�� �� ̰ �� �� ";
		m.gotoxy(35,8 + Y);	std::cout<<" 3 / Esc    �˳���Ϸ "; 
	
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED); //��ɫ 
		m.gotoxy(35,4 + Y);	std::cout<<" 1 / Enter  ��ʼ��Ϸ "; 

		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED); //��ɫ 
		m.gotoxy(35,6 + Y);	std::cout<<" 2 / Space  ��Ϸ˵�� "; 
		
		
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_BLUE); //��ɫ
		//����ѡ��ť 
		switch(choose)
		{
			case 0:	m.gotoxy(30 ,4 + Y);	std::cout<<" ->";	break; 	//��ʼ��Ϸ 
			case 1:	m.gotoxy(30 ,6 + Y);	std::cout<<" ->";	break; 	//��Ϸ˵�� 
			case 2:	m.gotoxy(30 ,8 + Y);	std::cout<<" ->";	break; 	//�˳���Ϸ 
		}
		
		m.gotoxy(0,11 + Y); //����ߵ�����λ�� 
	} 
	//���� 
	void Help()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int Y = csbi.dwCursorPosition.Y;		
	
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_GREEN); //����������ɫΪ��ɫ 
		std::cout<<"\t\t\t��������������������������������������������������������������������������������\n";	//0 
		std::cout<<"\t\t\t��                                      ��\n";
		std::cout<<"\t\t\t��������������������������������������������������������������������������������\n";	//2 
		std::cout<<"\t\t\t��                                      ��\n"; 
		std::cout<<"\t\t\t��                                      ��\n";	//4 
		std::cout<<"\t\t\t��           ��:W  ��:A  ��:S  ��:D     ��\n";
		std::cout<<"\t\t\t��                                      ��\n";	//6 
		std::cout<<"\t\t\t��                                      ��\n";
		std::cout<<"\t\t\t��           ����Ϸ��ɢ�������������   ��\n";	//8 
		std::cout<<"\t\t\t��       Ϸ�������޸ģ�����ѧϰ��       ��\n";
		std::cout<<"\t\t\t��                                      ��\n";	//10 
		std::cout<<"\t\t\t��  ������������������������������������������������������������������   ��\n"; 
		std::cout<<"\t\t\t��  �� ���� ��ѧϰ����               ��   ��\n";	//12 
		std::cout<<"\t\t\t��  ������������������������������������������������������������������   ��\n"; 
		std::cout<<"\t\t\t��  �� ���� ��2700768668@qq.com      ��   ��\n";	//14
		std::cout<<"\t\t\t��  ������������������������������������������������������������������   ��\n"; 
		std::cout<<"\t\t\t��������������������������������������������������������������������������������\n";	//16
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //��ɫ����
		m.gotoxy(40,1 + Y);		std::cout<<"˵  ��  ��  ";
		
		m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED); //��ɫ
		m.gotoxy(26,4 + Y);	std::cout<<"  ����˵��: ";
		m.gotoxy(26,7 + Y);	std::cout<<"  ��Ϸ���: ";
		m.gotoxy(35,17+ Y);
	} 
	//��ʼ��Ϸ 
	void Play()
	{
		Init();
		int c_0,move;
		while(1)
		{
			c_0 = clock();

			if	(( KEY_DOWN(VK_SPACE))) getch(); //�ո���ͣ 
			else if	(( KEY_DOWN('W') || KEY_DOWN(VK_UP)   ) && s.goal!=2)	goal = 0; //�� 
			else if	(( KEY_DOWN('A') || KEY_DOWN(VK_LEFT) ) && s.goal!=3) 	goal = 1; //�� 
			else if	(( KEY_DOWN('S') || KEY_DOWN(VK_DOWN) ) && s.goal!=0) 	goal = 2; //�� 
			else if	(( KEY_DOWN('D') || KEY_DOWN(VK_RIGHT)) && s.goal!=1) 	goal = 3; //��

			//�ƶ����
			if(c_0 - c_2 > 200)
			{
				c_1 = c_2; //�ƶ����˱ض�ˢ����Ļ 
				c_2 = c_0;
				s.goal = goal; //�����̵���ķ���ֵ���ߵķ��� 
				move = s.Move(f.Getx(),f.Gety(),1,1,_N-1,_N-1); //�ƶ� 
				
				if(move == 2) //ʳ�ﱻ����
				{
					f.New(1,1,_N-1,_N-1,s);
				}
				else if(move == 0) //ײ���� 
				{
					m.over(s,_N); //����game over ����
					m.setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED); //��ɫ
					std::cout<<"\n\t\t\t    GAME OVER! �ûس�����~";	//��ӡ������ʾ 
					while(getch()!=13); //�Ե�����̨���� 
					return; //�˳�Game.play() 
				}
			}
			
			//ˢ����� 
			if (c_0 - c_1 > 99)
			{
				c_1 = c_0;
				m.Show(f,s,_N);
			}

		}
	};
};
