#include "TurnstileGate.h"
#include <stdio.h>

TurnstileGate::TurnstileGate()
{
	state = locked;
}


TurnstileGate::~TurnstileGate()
{
}

int TurnstileGate::getState()
{
	return state;
}

void TurnstileGate::Lock()
{
	printf_s("Locked\n\n");
}

void TurnstileGate::Unlock()
{
	printf_s("Unlocked\n\n");
}

void TurnstileGate::Thankyou()
{
	printf_s("Thanks!\n\n");
}

void TurnstileGate::Alarm()
{
	printf_s("Alarm!\n\n");
}

void TurnstileGate::ResetAlarm()
{
	printf_s("Alarm reset\n\n");
}

void TurnstileGate::Violation()
{
	printf_s("Violation!\n\n");
}

void TurnstileGate::setState(int state)
{
	this->state = state;
}