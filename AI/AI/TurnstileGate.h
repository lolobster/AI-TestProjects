#pragma once
enum State
{
	locked = 1,
	unlocked = 2,
	violation = 3
	
};

class TurnstileGate
{
public:
	TurnstileGate();

	void Lock();
	void Unlock();
	void Thankyou();
	void ThankYouOff();
	void Alarm();
	void ResetAlarm();
	void Violation();
	int getState();
	void setState(int state);

	~TurnstileGate();
private:
	int state;
};

