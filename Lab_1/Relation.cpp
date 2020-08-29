#include "Relation.h"

Relation::Relation(size_t PIndex, size_t QIndex, size_t AIndex, size_t& MaxRIndex)
{
	this->PIndex = PIndex;
	this->QIndex = QIndex;
	this->AIndex = AIndex;
	this->index = MaxRIndex++;
}

void Relation::FromBinToVec(vector<Relation>& vr, size_t& MaxRIndex)
{
	ifstream ReadStream("RelationBase", ios::in | ios::binary);
	int AmountOfRelations;
	ReadStream.read((char*)&AmountOfRelations, sizeof(AmountOfRelations));
	vr.resize(AmountOfRelations);
	ReadStream.read((char*)&MaxRIndex, sizeof(MaxRIndex));
	for (int i = 0; i < AmountOfRelations; i++)
	{
		ReadStream.read((char*)&vr[i], sizeof(vr[i]));
	}
	ReadStream.close();
}

void Relation::FromVecToBin(vector<Relation>& vr, size_t& MaxRIndex)
{
	ofstream WriteStream("RelationBase", ios::binary | ios::out);
	auto size = vr.size();
	WriteStream.write((char*)&size, sizeof(vr.size()));
	WriteStream.write((char*)&MaxRIndex, sizeof(MaxRIndex));
	for (int i = 0; i < vr.size(); i++)
		WriteStream.write((char*)&vr[i], sizeof(vr[i]));
	WriteStream.close();
}

size_t Relation::GetPIndex()
{
	return PIndex;
}

size_t Relation::GetQIndex()
{
	return QIndex;
}

size_t Relation::GetAIndex()
{
	return AIndex;
}
