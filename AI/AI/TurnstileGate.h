#pragma once
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

	~TurnstileGate();
private:

};

