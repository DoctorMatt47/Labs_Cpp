#include "Monomial.h"

Monomial::Monomial()
{
	power = 0;
	ratio = 0;
}

Monomial::Monomial(size_t ratio, size_t power)
{
	this->ratio = ratio;
	this->power = power;
}

void Monomial::print()
{
	if (ratio == 1 && power != 0)
	{

	}
	else
		std::cout << ratio;
	if(power > 1)
		std::cout << "x^" << power;
	if (power == 1)
		std::cout << "x";
}

double Monomial::getRatio()
{
	return ratio;
}

size_t Monomial::getPower()
{
	return power;
}
