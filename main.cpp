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
		
		//按压方向键 
		if(ch==224)  
		{
			ch = getch();
			switch(ch)
			{
				case 72: case 75: 	choose--;	break;//上左 
				case 77: case 80:	choose++;	break;//下右 
			}
			choose+=3; choose%=3;
		}
		//敲回车或空格 
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
		//按Esc快速退出 
		if(ch == 27)
		{
			exit(1);
		}
	}
	return 0;
}
