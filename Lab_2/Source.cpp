#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include "Monomial.h"
#include "Polynomial.h"

void MainMenu();
void DividePolynomial(std::vector<Polynomial>& vPoly);
void CreatePoly(std::vector<Polynomial>& vPoly);
void ChangePolynomial(std::vector<Polynomial>& vPoly);
void PrintPolynomials(std::vector<Polynomial>& vPoly);
void DeletePolynomial(std::vector<Polynomial>& vPoly);
void ReadFromFile(std::vector<Polynomial>& vPoly);
void WriteToFile(std::vector<Polynomial>& vPoly);
void DeleteFromFile();

int state = 1;

int main()
{
	std::vector<Polynomial> vPoly;

	MainMenu();
	while (state > 0 && state <= 9)
	{
		switch (state)
		{
		case 1:
		{
			DividePolynomial(vPoly);
			break;
		}
		case 2:
		{	
			system("cls");
			std::cout << "(0)Exit\n";
			PrintPolynomials(vPoly);
			std::cin.get();
			std::cin.get();
			MainMenu();
			break;
		}
		case 3:
		{
			CreatePoly(vPoly);
			break;
		}
		case 4:
		{
			ChangePolynomial(vPoly);
			break;
		}
		case 5:
		{
			DeletePolynomial(vPoly);
			break;
		}
		case 6:
		{
			system("cls");
			std::cout << "(0)Exit\n";
			Polynomial::PrintFromBin();
			std::cin.get();
			std::cin.get();
			MainMenu();
			break;
		}
		case 7:
		{
			ReadFromFile(vPoly);
			break;
		}
		case 8:
		{
			WriteToFile(vPoly);
			break;
		}
		case 9:
		{
			DeleteFromFile();
			break;
		}
		default:
			break;
		}
	}
	return 0;
}

void ChangePolynomial(std::vector<Polynomial>& vPoly)
{
	size_t numPol;
	system("cls");
	std::cout << "Choose which polynomial do you want to change\n";
	std::cout << "(0)Exit\n";
	PrintPolynomials(vPoly);
	std::cin >> numPol;
	numPol--;
	if (numPol >= 0 && numPol < vPoly.size())
	{
		size_t pState;
		vPoly[numPol].print();
		std::cout << "(0)Exit\n"
			<< "(1)Add power\n"
			<< "(2)Delete power\n";
		std::cin >> pState;
		if (pState == 1)
		{
			size_t rat;
			std::cout << "Enter ratio\n";
			std::cin >> rat;
			Monomial newM(rat, vPoly[numPol].get_size());
			system("cls");
			std::cout << "Your polynomial has been changed successfully\n";
			vPoly[numPol].push_front(newM);
			vPoly[numPol].print();
			std::cin.get();
			std::cin.get();
		}
		else if (pState == 2)
		{
			if (vPoly[numPol].get_size() == 1)
			{
				std::cout << "Your polynomial has been deleted successfully\n";
				vPoly[numPol].print();
				vPoly[numPol].pop();
				vPoly.erase(vPoly.begin() + numPol);
				std::cin.get();
				std::cin.get();
			}
			else if (vPoly[numPol].get_size() > 1)
			{
				vPoly[numPol].pop_front();
				std::cout << "Your polynomial has been changed successfully\n";
				vPoly[numPol].print();
				std::cin.get();
				std::cin.get();
			}
		}
	}
	MainMenu();
}

void MainMenu()
{
	system("cls");
	std::cout << "(0)Exit\n"
		<< "(1)Divide polynomial\n"
		<< "(2)Print polynomial\n"
		<< "(3)Create polynomial\n"
		<< "(4)Change polynomial\n"
		<< "(5)Delete polynomial\n"
		<< "(6)Print from file\n"
		<< "(7)Read from file\n"
		<< "(8)Write to file\n"
		<< "(9)Delete from file\n";
	std::cin >> state;
}

void DividePolynomial(std::vector<Polynomial>& vPoly)
{
	size_t numPol;
	system("cls");

	std::cout << "Choose your polynomial\n";
	std::cout << "(0)Exit\n";
	PrintPolynomials(vPoly);
	std::cin >> numPol;
	numPol--;
	if (numPol >= 0 && numPol < vPoly.size())
	{
		size_t div;
		std::vector<unsigned long long> vRem;
		vPoly[numPol].print();
		std::cout << "Enter divider\n";
		std::cin >> div;
		for (size_t i = 0; i <= div - 1; i++)
		{
			bool ex = false;
			unsigned long long rem = vPoly[numPol].Sum(i) % div;
			for (size_t j = 0; j < vRem.size(); j++)
			{
				if (rem == vRem[j])
				{
					ex = true;
					break;
				}
			}
			if (!ex)
			{
				vRem.push_back(rem);
			}
		}
		system("cls");
		vPoly[numPol].print();
		std::cout << "Remainders:\n";
		for (size_t i = 0; i < vRem.size(); i++)
		{
			std::cout << vRem[i] << std::endl;
		}
		std::cin.get();
		std::cin.get();
	}

	MainMenu();
}

void CreatePoly(std::vector<Polynomial>& vPoly)
{
	system("cls");

	int polypower;
	std::cout << "Enter polynomial power\n";
	std::cin >> polypower;
	Polynomial NewPoly;
	for (int i = polypower; i >= 0; i--)
	{
		size_t ratio;
		std::cout << polypower - i + 1 << " ratio:\n";
		std::cin >> ratio;
		if (ratio > 0)
		{
			Monomial NewMono(ratio, i);
			NewPoly.push_back(NewMono);
		}
	}
	std::cout << "Your polynomial has been created successfully\n";
	NewPoly.print();
	std::cin.get();
	std::cin.get();
	vPoly.push_back(NewPoly);
	MainMenu();
}

void PrintPolynomials(std::vector<Polynomial>& vPoly)
{
	if (vPoly.size() != 0)
		for (size_t i = 0; i < vPoly.size(); i++)
		{
			std::cout << "(" << i + 1 << ")";
			vPoly[i].print();
		}
	else
	{
		std::cout << "\nPolynomials is not exist\n";
	}
}

void DeletePolynomial(std::vector<Polynomial>& vPoly)
{
	size_t numPol;
	system("cls");

	std::cout << "Choose which polynomial do you want to delete\n";
	std::cout << "(0)Exit\n";
	PrintPolynomials(vPoly);
	std::cin >> numPol;
	numPol--;
	system("cls");
	if (numPol >= 0 && numPol < vPoly.size())
	{
		std::cout << "Your polynomial has been deleted successfully\n";
		vPoly[numPol].print();
		vPoly[numPol].pop();
		vPoly.erase(vPoly.begin() + numPol);
		std::cin.get();
		std::cin.get();
	}
	MainMenu();
}

void WriteToFile(std::vector<Polynomial>& vPoly)
{
	size_t numPol;
	system("cls");

	std::cout << "Choose which polynomial do you want to write\n";
	std::cout << "(0)Exit\n";
	PrintPolynomials(vPoly);
	std::cin >> numPol;
	numPol--;
	if (numPol >= 0 && numPol < vPoly.size())
	{
		vPoly[numPol].WriteToBin();
		std::cout << "Your polynomial has been written successfully\n";
		vPoly[numPol].print();
		std::cin.get();
		std::cin.get();
	}
	MainMenu();
}

void ReadFromFile(std::vector<Polynomial>& vPoly)
{
	Polynomial newPol;
	size_t pNum;
	system("cls");

	std::cout << "Choose which polynomial do you want to read\n";
	std::cout << "(0)Exit\n";
	size_t count = Polynomial::PrintFromBin();
	std::cin >> pNum;
	pNum--;
	if (pNum >= 0 && pNum <= count)
	{
		system("cls");
		newPol.ReadFromBin(pNum);
		std::cout << "Your polynomial has been read successfully\n";
		newPol.print();
		vPoly.push_back(newPol);
		std::cin.get();
		std::cin.get();
	}
	MainMenu();
}

void DeleteFromFile()
{
	size_t size;
	size_t numPol;
	system("cls");
	std::cout << "Choose which polynomial do you want do delete\n";
	std::cout << "(0)Exit\n";
	size = Polynomial::PrintFromBin();
	std::cin >> numPol;
	numPol--;
	if (numPol >= 0 && numPol < size)
	{
		std::cout << "Your polynomial has been deleted successfully\n";
		Polynomial::DeleteFromBin(numPol);
		std::cin.get();
		std::cin.get();
	}
	MainMenu();
}