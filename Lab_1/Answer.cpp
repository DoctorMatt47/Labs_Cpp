#include "Answer.h"

Answer::Answer(const char answ[256], size_t QuestIndex, size_t& MaxIndex)
{
	strncpy_s(this->answ, answ, 256);
	index = MaxIndex++;
	this->QuestIndex = QuestIndex;
}

int Answer::GetQuestIndex()
{
	return QuestIndex;
}

int Answer::GetIndex()
{
	return index;
}

void Answer::PrintAnswer()
{
	cout << answ << endl;
}

void Answer::FromBinToVec(vector<Answer>& va, size_t& MaxAIndex)
{
	ifstream ReadStream("AnswerBase", ios::in | ios::binary);
	int AmountOfAnswers;
	ReadStream.read((char*)&AmountOfAnswers, sizeof(AmountOfAnswers));
	va.resize(AmountOfAnswers);
	ReadStream.read((char*)&MaxAIndex, sizeof(MaxAIndex));
	for (int i = 0; i < AmountOfAnswers; i++)
	{
		ReadStream.read((char*)&va[i], sizeof(va[i]));
	}
	ReadStream.close();
}

void Answer::FromVecToBin(vector<Answer>& va, size_t& MaxAIndex)
{
	ofstream WriteStream("AnswerBase", ios::binary | ios::out);
	auto size = va.size();
	WriteStream.write((char*)&size, sizeof(va.size()));
	WriteStream.write((char*)&MaxAIndex, sizeof(MaxAIndex));
	for (int i = 0; i < va.size(); i++)
		WriteStream.write((char*)&va[i], sizeof(va[i]));
	WriteStream.close();
}
