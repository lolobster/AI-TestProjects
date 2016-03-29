#include "TurnstileFSM.h"
#include <Windows.h>
#include <iostream>
#include <string>

int main()
{
	TurnstileFSM ts;
// User input
	std::cout << "paina nappia(1-4) keijo: ";


	
	if (GetAsyncKeyState(1))
	{
		ts.Coin();
	}
	if (GetAsyncKeyState(2))
	{
		ts.Pass();
	}
	if (GetAsyncKeyState(3))
	{
		ts.Reset();
	}
	if (GetAsyncKeyState(4))
	{
		ts.Ready();
	}
	
	system("pause");
}