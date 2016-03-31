#include "TurnstileFSM.h"
#include <Windows.h>
#include <iostream>
#include <string>

bool keyPressed(int key)
{
	return (GetAsyncKeyState(key) & 0x8000);
}

void menu()
{
	std::cout << "1 - Coin" << std::endl;
	std::cout << "2 - Pass" << std::endl;
	std::cout << "3 - Reset" << std::endl;
	std::cout << "4 - Ready" << std::endl;
	std::cout << "0 - Exit" << std::endl << std::endl;
	std::cout << "Press a button (0-4): ";
	Sleep(1000);
}

int main()
{
	TurnstileFSM ts;
	
	bool exit = false;

	menu();

	while (exit != true){
		if (GetAsyncKeyState(0x31))
		{
			ts.Coin();
			menu();
		}
		if (GetAsyncKeyState(0x32))
		{
			ts.Pass();
			menu();
		}
		if (GetAsyncKeyState(0x33))
		{
			ts.Reset();
			menu();
		}
		if (GetAsyncKeyState(0x34))
		{
			ts.Ready();
			menu();
		}
		if (GetAsyncKeyState(0x30))
		{
			printf_s("Exit chosen!\n");
			printf_s("\n\n");
			exit = true;
		}
	}
	system("pause");
}