#pragma once
#include "TurnstileGate.h"
#include "TurnstileState.h"
class TurnstileFSM
	: public TurnstileGate, public TurnstileState
{
public:
	TurnstileFSM();

	virtual void Coin();
	virtual void Pass();
	void Reset();
	void Ready();
	void SetState(TurnstileState tss);

	virtual~TurnstileFSM();
};

