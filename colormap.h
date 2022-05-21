#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "snake.h"
#include "food.h"

#define maxn 20

class Map{
	int map[maxn][maxn];
	
	HANDLE hOutput; //����̨������
	
	CONSOLE_CURSOR_INFO cci; //�������� 
	DWORD bytes;
	
	char data[8000]; //������ 
	
	/*��ʼ���յ�ͼ����*/ 
	void Init(int n)
	{
		int i,j;
		for(i=0;i < n;i++)
		{
			for(j=0;j < n;j++)
			{
				if(i == 0 || i==n-1) map[j][i] = 1; //ǽ�ڵı�־
				else if(j == 0 || j==n-1) map[j][i] = 1; //ǽ�ڵı�־
				else map[j][i] = 0; //û�ж���
			}
		}
	} 
	/*��ӡ�б�*/
	void Out(int n)
	{	
		static bool flag=0; //ʳ����˸��� 
		int i,j;
	
		gotoxy(0,0);
		for(j=0;j<n;j++)
		{
			std::cout<<std::endl<<"\t\t\t ";
			for(i=0;i<n;i++)
			{
				switch(map[j][i])
				{
					case 0:	std::cout<<"   ";	break; //û�ж���
					case 1: 
							setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); //��ɫ����
							std::cout<<"[+]"; 	break; //ǽ�� 
					case 2: 
							setcolor(FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN); //��ɫ+��ɫ���� 
							std::cout<<(flag?"*+*":" * ");
							flag=!flag; 		break; //ʳ��
					case 3: 
							setcolor(FOREGROUND_INTENSITY|FOREGROUND_GREEN);//��ɫ���� 
							std::cout<<"(O)"; 	break; //����
					case 4: 
							setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED);//��ɫ���� 
							std::cout<<"(X)"; 	break; //��ͷ
					case 5: 
							setcolor(FOREGROUND_INTENSITY|FOREGROUND_RED);//��ɫ���� 
							std::cout<<" * "; 	break; //��ɾ��
				}
			}
		}
	} 
	
public:
	//c++��gotoxy���� 
	void gotoxy(int x,int y)                
	{
		COORD c={x,y};
		SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE),c);
	}
	//c++��setcolor����    
	void setcolor(WORD wAttributes)                
	{
		SetConsoleTextAttribute(hOutput, wAttributes);

//		wAttributes			    ��ɫ			��Ӧ��ֵ
//		
//		FOREGROUND_BLUE			������ɫ���� 		1
//		FOREGROUND_GREEN 		������ɫ���� 		2
//		FOREGROUND_RED 			������ɫ���� 		4
//		FOREGROUND_INTENSITY 	ǰ��ɫ������ʾ 		8
//		BACKGROUND_BLUE 		������ɫ����  		16
//		BACKGROUND_GREEN 		������ɫ���� 		32
//		BACKGROUND_RED 			������ɫ���� 		64
//		BACKGROUND_INTENSITY 	����ɫ������ʾ 		128
	}
	Map(){
	
		system("color 0A");
	    //��ȡĬ�ϱ�׼��ʾ���������
	    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	 
	    //���ػ������Ĺ��
	    cci.bVisible = 0;
	    cci.dwSize = 1;
	    SetConsoleCursorInfo(hOutput, &cci);
	}
	void Show(Food f,Snake s,int n)//n�����ͼ�Ŀ�� 
	{
		
		Body *p;
		
		//��ʼ���յ�ͼ����
		Init(n);
		
		//��ʳ��������ӵ���ͼ���� 
		map[f.Gety()][f.Getx()] = 2; //ʳ���־
		
		//�������������ӵ���ͼ���� s
		for(p=s.Get()->next; p->next!=NULL; p = p->next)
		{
			map[p->y][p->x] = 3; //������ı�־
		}
		//����ͷ��ӵ���ͼ���� 
		map[p->y][p->x] = 4;// ��ͷ�ı�־

		//��ӡ��ͼ
		Out(n);
		//��ӡ�ɼ�
		std::cout<<"\n\n\t\t\t\t �÷֣�"<<s.lenth()-3; 
	}
	void over(Snake s,int n)
	{
		Body *p,*pre;
		int time = s.lenth()>10 ? 100:200-s.lenth()*10; 
		while(s.Get()->next)
		{	
			//��ʼ���յ�ͼ����
			Init(n);
		
			//�������������ӵ���ͼ���� s
			for(pre=s.Get(),p=pre->next; p->next!=NULL; p=p->next)
			{
				pre = p;
				map[p->y][p->x] = 3; //������ı�־
			}
					
			//����ͷ��ӵ���ͼ����
			map[p->y][p->x] = 5; //��ͷ��ɾ���ı�־
			
			//��ӡ��ͼ 
			Out(n);	
			//��ӡ�÷�	
			std::cout<<"\n\n\t\t\t\t �÷֣�"<<s.lenth()-3; 
			
			//ɾ����ͷ 
			pre->next = NULL;
			delete(p);
			Sleep(time);
		}
	}
	
};

