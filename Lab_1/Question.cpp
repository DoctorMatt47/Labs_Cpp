#include "Question.h"

Question::Question(const char quest[256], unsigned int& MaxQIndex)
{
	strncpy_s(this->quest, quest, 256);
	this->index = MaxQIndex++;
}

int Question::GetIndex()
{
	return index;
}

void Question::PrintQuest()
{
	std::cout << quest << endl;
}

void Question::FromBinToVec(vector<Question>& vq, size_t& MaxQIndex)
{
	ifstream ReadStream("QuestionBase", ios::binary | ios::in);
	size_t AmountOfQuest;
	ReadStream.read((char*)&AmountOfQuest, sizeof(AmountOfQuest));
	vq.resize(AmountOfQuest);
	ReadStream.read((char*)&MaxQIndex, sizeof(MaxQIndex));
	for (int i = 0; i < AmountOfQuest; i++)
	{
		ReadStream.read((char*)&vq[i], sizeof(vq[i]));
	}
	ReadStream.close();
}

void Question::FromVecToBin(vector<Question>& vq, size_t& MaxQIndex)
{
	ofstream WriteStream("QuestionBase", ios::binary | ios::out);
	auto size = vq.size();
	WriteStream.write((char*)&size, sizeof(vq.size()));
	WriteStream.write((char*)&MaxQIndex, sizeof(MaxQIndex));
	for (int i = 0; i < vq.size(); i++)
		WriteStream.write((char*)&vq[i], sizeof(vq[i]));
	WriteStream.close();
}