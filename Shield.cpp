#include "Shield.h"

Shield::Shield()
{
	initHP();
}

Shield::~Shield()
{
}

void Shield::initHP()
{
	this->hpMax = 400;
	this->hp = this->hpMax;
}

float Shield::getHp()
{
	return this->hp;
}

float Shield::getHpMax()
{
	return this->hpMax;
}

void Shield::loseHP(int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}
