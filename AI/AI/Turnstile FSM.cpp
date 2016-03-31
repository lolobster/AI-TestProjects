#include "TurnstileFSM.h"
#include <stdio.h>


TurnstileFSM::TurnstileFSM()
{
	gate.Lock();
}


TurnstileFSM::~TurnstileFSM()
{
}

void TurnstileFSM::Coin()
{
	switch (gate.getState())
	{
	case locked:
	{
		gate.Unlock();
		break;
	}
	case unlocked:
	{
		gate.Thankyou();
		break;
	}
	case violation:
	{
		gate.Violation();
		break;
	}
	default:
		break;
	}
}

void TurnstileFSM::Pass()
{
	switch (gate.getState())
	{
	case locked:
	{
		gate.Alarm();
		break;
	}
	case unlocked:
	{
		gate.Lock();
		break;
	}
	case violation:
	{
		gate.Violation();
		break;
	}
	default:
		break;
	}
}

void TurnstileFSM::Reset()
{
	if (gate.getState() == violation)
	{
		gate.ResetAlarm();
		Ready();
	}
	else
	{
		printf_s("Nothing to reset\n\n");
	}
}

void TurnstileFSM::Ready()
{
	gate.ResetAlarm();
	gate.Lock();
}

void TurnstileFSM::SetState(int state)
{
	gate.setState(state);
}

int TurnstileFSM::GetState()
{
	return gate.getState();
}