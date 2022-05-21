#include <iostream>
#include "game.h"

int main()
{
	Game game;
	int choose=0;
	int ch;
	
	while(1)
	{
		game.Menu(choose);
		ch = getch();
		
		//��ѹ����� 
		if(ch==224)  
		{
			ch = getch();
			switch(ch)
			{
				case 72: case 75: 	choose--;	break;//���� 
				case 77: case 80:	choose++;	break;//���� 
			}
			choose+=3; choose%=3;
		}
		//�ûس���ո� 
		if(ch==32 || ch == 13)
		{
			switch(choose)
			{
				case 0:	game.Play(); 	break;      
				case 1:	game.Help();	getch();	break;
				case 2:	exit(1);
			}
			system("cls"); 
		}
		//��Esc�����˳� 
		if(ch == 27)
		{
			exit(1);
		}
	}
	return 0;
}
