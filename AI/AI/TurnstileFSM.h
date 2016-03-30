#pragma once
#include "TurnstileGate.h"

class TurnstileFSM
	: public TurnstileGate
{
public:
	TurnstileFSM();

	void Coin();
	void Pass();
	void Reset();
	void Ready();
	void SetState(int state);
	int GetState();

	virtual~TurnstileFSM();

private:
	TurnstileGate gate;
};

