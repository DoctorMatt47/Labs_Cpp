#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Answer
{
private:

	char answ[256];
	size_t QuestIndex;
	size_t index;

public:

	Answer() {};

	Answer(const char answ[256], size_t QuestIndex, size_t& MaxIndex);

	int GetQuestIndex();

	int GetIndex();

	void PrintAnswer();

	static void FromBinToVec(vector<Answer>& va, size_t& MaxAIndex);

	static void FromVecToBin(vector<Answer>& va, size_t& MaxAIndex);
};

