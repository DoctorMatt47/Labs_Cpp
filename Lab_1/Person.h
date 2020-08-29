#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Question.h"
#include "Answer.h"

using namespace std;

class Person
{
private:

	char name[64];
	size_t index;

public:

	Person() {};

	Person(const char name[64], size_t& MaxIndex);

	static void FromBinToVec(vector<Person>& vecP, size_t& MaxPIndex);

	static void FromVecToBin(vector<Person>& vp, size_t& MaxPIndex);

	char* GetName();

	size_t GetIndex();
};

