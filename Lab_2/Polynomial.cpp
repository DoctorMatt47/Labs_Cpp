#include "Polynomial.h"
#include "Monomial.h"
#include <fstream>

Polynomial::Polynomial()
{
	Head = nullptr;
	Tail = nullptr;
	Size = 0;
}

Polynomial::Polynomial(const Polynomial& other)
{
	this->Head = nullptr;
	this->Tail = nullptr;
	this->Size = 0;
	Node* otherCur = other.Head;
	for (size_t i = 0; i < other.Size; i++)
	{
		Monomial buff;
		buff = otherCur->data;
		this->push_back(buff);
		otherCur = otherCur->pNext;
	}
}

//Polynomial::Polynomial(Polynomial&& other)
//{
//	this->Head = other.Head;
//	this->Tail = other.Tail;
//	this->Size = other.Size;
//	other.Head = nullptr;
//	other.Tail = nullptr;
//}

Polynomial::~Polynomial()
{
	while (Size != 0)
	{
		pop_front();
	}
}

void Polynomial::push_back(Monomial data)
{
	if (Size == 0)
	{
		Head = new Node;
		Head->data = data;
		Head->pPrev = nullptr;
		Head->pNext = nullptr;
		Tail = Head;
	}
	else
	{
		Node* NewTail = new Node;
		NewTail->data = data;
		Tail->pNext = NewTail;
		NewTail->pPrev = Tail;
		Tail = NewTail;
	}
	Size++;
}

void Polynomial::push_front(Monomial data)
{
	if (Size == 0)
	{
		Head = new Node;
		Head->data = data;
		Head->pPrev = nullptr;
		Head->pNext = nullptr;
		Tail = Head;
	}
	else
	{
		Node* NewHead = new Node;
		NewHead->data = data;
		Head->pPrev = NewHead;
		NewHead->pNext = Head;
		Head = NewHead;
	}
	Size++;
}

void Polynomial::pop_front()
{
	if (Size == 1)
	{
		delete Head;
		Head = nullptr;
		Tail = nullptr;
	}
	else if (Size > 1)
	{
		Node* NewHead = Head->pNext;
		delete Head;
		NewHead->pPrev = nullptr;
		Head = NewHead;
	}
	Size--;
}

void Polynomial::pop_back()
{
	if (Size == 1)
	{
		delete Head;
		Head = nullptr;
		Tail = nullptr;
	}
	else if (Size > 1)
	{
		Node* NewTail = Head->pPrev;
		NewTail->pNext = nullptr;
		delete Tail;
		Tail = NewTail;
	}
	Size--;
}

size_t Polynomial::get_size()
{
	return Size;
}

void Polynomial::pop()
{
	while (Size != 0)
	{
		pop_front();
	}
}

void Polynomial::print()
{
	if (Size != 0)
	{
		Node* current = this->Head;
		current->data.print();
		while (current->pNext != nullptr)
		{
			current = current->pNext;
			std::cout << " + ";
			current->data.print();
		}
		std::cout << std::endl;
	}
}

Monomial& Polynomial::operator[](size_t it)
{
	if (it < Size)
	{
		if (it < Size / 2)
		{
			Node* current = Head;
			for (size_t i = 0; i < it; i++)
				current = current->pNext;
			return current->data;
		}
		else
		{
			Node* current = Tail;
			for (size_t i = 0; i < it; i++)
				current = current->pPrev;
			return current->data;
		}
	}
}

void Polynomial::WriteToBin()
{
	std::ifstream orig("Polynomial", std::ios::binary | std::ios::in);
	orig.seekg(0, std::ios::end);
	if (orig.tellg() != 0)
	{
		orig.seekg(0, std::ios::beg);
		std::ofstream copy("PolynomialCOPY", std::ios::binary | std::ios::out);
		copy << orig.rdbuf();

		copy.write((char*)&Size, sizeof(Size));
		Node* current = Tail;
		for (size_t i = 0; i < Size; i++)
		{
			Monomial buff = current->data;
			copy.write((char*)&buff, sizeof(buff));
			current = current->pPrev;
		}
		orig.close();
		copy.close();

		std::ofstream orig_new("Polynomial", std::ios::binary | std::ios::out);
		std::ifstream copy_new("PolynomialCOPY", std::ios::binary | std::ios::in);
		orig_new << copy_new.rdbuf();
		orig_new.close();
		copy_new.close();
	}
	else
	{
		orig.close();
		std::ofstream orig("Polynomial", std::ios::binary | std::ios::out);
		orig.write((char*)&Size, sizeof(Size));
		Node* current = Head;
		for (size_t i = 0; i < Size; i++)
		{
			Monomial buff = current->data;
			orig.write((char*)&buff, sizeof(buff));
			current = current->pNext;
		}
		orig.close();
	}
}

void Polynomial::ReadFromBin(size_t index)
{
	std::ifstream re("Polynomial", std::ios::binary | std::ios::in);
	size_t size;
	for (size_t i = 0; i < index; i++)
	{
		re.read((char*)&size, sizeof(size));
		re.seekg(size * sizeof(Monomial), std::ios::cur);
	}
	re.read((char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		Monomial buff;
		re.read((char*)&buff, sizeof(buff));
		push_front(buff);
	}
}

void Polynomial::DeleteFromBin(size_t index)
{
	bool end = false;
	std::ifstream orig("Polynomial", std::ios::binary | std::ios::in);
	orig.seekg(0, std::ios::end);
	size_t counter = 0;
	if (orig.tellg() != 0)
	{
		orig.seekg(0, std::ios::beg);
		std::ofstream copy("PolynomialCOPY", std::ios::binary | std::ios::out);

		while (!end)
		{
				size_t size;
				orig.read((char*)&size, sizeof(size));
				if (counter != index)
				{
					if (!orig.eof())
					{
						copy.write((char*)&size, sizeof(size));
						for (size_t i = 0; i < size; i++)
						{
							Monomial buff;
							orig.read((char*)&buff, sizeof(buff));
							copy.write((char*)&buff, sizeof(buff));
						}
					}
					else
						end = true;
				}
				else
				{
					orig.seekg(size * sizeof(Monomial), std::ios::cur);
				}
				counter++;
		}
		orig.close();
		copy.close();
		std::ofstream orig_new("Polynomial", std::ios::binary | std::ios::out);
		std::ifstream copy_new("PolynomialCOPY", std::ios::binary | std::ios::in);
		orig_new << copy_new.rdbuf();
		orig_new.close();
		copy_new.close();
	}
}

size_t Polynomial::PrintFromBin()
{
	size_t count = 1;
	bool is_empty = false;
	std::ifstream re("Polynomial", std::ios::binary | std::ios::in);
	while (!is_empty)
	{
		Polynomial pbuff;
		Monomial mbuff;
		size_t size;
		re.read((char*)&size, sizeof(size));
		for (size_t i = 0; i < size; i++)
		{
			re.read((char*)&mbuff, sizeof(mbuff));
			pbuff.push_front(mbuff);
		}
		if (re.eof())
			is_empty = true;
		else
		{
			std::cout << "(" << count << ")";
			pbuff.print();
			count++;
		}
	}
	return count - 1;
}

unsigned long long Polynomial::Sum(size_t x)
{
	long long sum = 0;
	Node* current = Head;
	if (x != 0)
	{
		while (current != nullptr)
		{
			if (current->data.getPower() != 0)
			{
				sum += current->data.getRatio() * pow(x, current->data.getPower());
				current = current->pNext;
			}
			else
			{
				sum += current->data.getRatio();
				current = current->pNext;
			}
		}
	}
	else
		while (current != nullptr)
		{
			if (current->data.getPower() != 0)
			{
				current = current->pNext;
			}
			else
			{
				sum = current->data.getRatio();
				break;
			}
		}
	return sum;
}

