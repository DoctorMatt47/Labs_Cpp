#include "Person.h"

Person::Person(const char name[64], size_t& MaxIndex)
{
	strncpy_s(this->name, name, 64);
	this->index = MaxIndex++;
}

void Person::FromBinToVec(vector<Person>& vp, size_t& MaxPIndex)
{
	ifstream ReadStream("PersonBase", ios::in | ios::binary);
	size_t AmountOfPerson;
	ReadStream.read((char*)&AmountOfPerson, sizeof(AmountOfPerson));
	vp.resize(AmountOfPerson);
	ReadStream.read((char*)&MaxPIndex, sizeof(MaxPIndex));
	for(int i = 0; i < AmountOfPerson; i++)
		ReadStream.read((char*)&vp[i], sizeof(vp[i]));
	ReadStream.close();
}

void Person::FromVecToBin(vector<Person>& vp, size_t& MaxPIndex)
{
	ofstream WriteStream("PersonBase", ios::binary | ios::out);
	size_t size = vp.size();
	WriteStream.write((char*)&size, sizeof(vp.size()));
	WriteStream.write((char*)&MaxPIndex, sizeof(MaxPIndex));
	for (int i = 0; i < vp.size(); i++)
		WriteStream.write((char*)&vp[i], sizeof(vp[i]));
	WriteStream.close();
}

char* Person::GetName()
{
	return name;
}

size_t Person::GetIndex()
{
	return index;
}
