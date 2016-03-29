#pragma once
#include "TurnstileFSM.h"

class TurnstileState
{
public:
	TurnstileState();
	void Coin(TurnstileFSM);
	void Pass(TurnstileFSM);

	~TurnstileState();
};

