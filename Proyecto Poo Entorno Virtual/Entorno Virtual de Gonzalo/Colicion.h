#pragma once
class Colicion
{
public:
	float MenorX;
	float MayorX;
	float MenorZ;
	float MayorZ;

	bool InX{ false };
	bool InZ{ false };

	Colicion(float MenorX, float MayorX, float MenorZ, float MayorZ);
	~Colicion();
	void SetCollition(float MenorX, float MayorX, float MenorZ, float MayorZ)
	{
		this->MenorX = MenorX;
		this->MayorX = MayorX;
		this->MenorZ = MenorZ;
		this->MayorZ = MayorZ;
	}

	bool isCollition(float x, float z);
};

