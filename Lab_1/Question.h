#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Question
{
private:

	char quest[256];
	size_t index;

public:

	Question() {};

	Question(const char quest[256], size_t& MaxQIndex);

	int GetIndex();

	void PrintQuest();

	static void FromBinToVec(vector<Question>& vq, size_t& MaxQIndex);

	static void FromVecToBin(vector<Question>& vq, size_t& MaxQIndex);
};