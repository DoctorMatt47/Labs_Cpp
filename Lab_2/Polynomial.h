#pragma once
#include "Monomial.h"

class Polynomial
{
private:

	class Node
	{
	public:
		Monomial data;
		Node* pNext;
		Node* pPrev;

		Node()
		{
			pNext = nullptr;
			pPrev = nullptr;
			data = Monomial();
		}
	};

	Node* Head;
	Node* Tail;
	size_t Size;

public:

	Polynomial();

	Polynomial(const Polynomial& other);

	//Polynomial(Polynomial&& other);

	~Polynomial();

	void push_back(Monomial data);

	void push_front(Monomial data);

	void pop_front();

	void pop_back();

	size_t get_size();

	void pop();

	void print();

	Monomial& operator [](size_t it);

	void WriteToBin();

	void ReadFromBin(size_t index);

	static size_t PrintFromBin();

	static void DeleteFromBin(size_t index);

	unsigned long long Sum(size_t x);
};