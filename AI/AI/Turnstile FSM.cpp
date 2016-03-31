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
		gate.Violation();
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
	if (gate.getState() == violation)
	{
		gate.ResetAlarm();
		gate.Lock();
	}
	else
		printf_s("Violation state not active!\n\n");
}

void TurnstileFSM::SetState(int state)
{
	gate.setState(state);
}

int TurnstileFSM::GetState()
{
	return gate.getState();
}