#pragma once
#include <iostream>
class Monomial
{
private:
	size_t ratio;
	size_t power;
public:

	Monomial();

	Monomial(size_t ratio, size_t power);

	void print();

	double getRatio();

	size_t getPower();
};

