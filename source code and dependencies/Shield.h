#pragma once
class Shield
{
private:
	int hpMax, hp;

public:
	//cons decons

	Shield();
	virtual ~Shield();

	void initHP();

	float getHp();
	float getHpMax();
	
	void loseHP(int value);

};

