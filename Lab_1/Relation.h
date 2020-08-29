#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Relation
{
private:

	size_t PIndex;
	size_t QIndex;
	size_t AIndex;
	size_t index;

public:
	Relation() {};

	Relation(size_t PIndex, size_t QIndex, size_t AIndex, size_t& MaxRIndex);

	static void FromBinToVec(vector<Relation>& vr, size_t& MaxRIndex);

	static void FromVecToBin(vector<Relation>& vr, size_t& MaxRIndex);

	void PrintInfo()
	{

	}

	size_t GetPIndex();

	size_t GetQIndex();

	size_t GetAIndex();
};

