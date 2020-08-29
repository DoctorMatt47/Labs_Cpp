#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <string>
#include "Question.h"
#include "Answer.h"
#include "Person.h"
#include "Relation.h"

int state;
size_t MaxQIndex = 0;
size_t MaxAIndex = 0;
size_t MaxPIndex = 0;
size_t MaxRIndex = 0;

void MainMenu();
void PrintQuestions(vector<Question>& vecQ);
void Test(vector<Question>& vecQuest, vector<Answer>& vecAnsw, vector<Person>& vecPerson, vector<Relation>& vecRelation);
void AddNewQuestion(vector<Question>& vecQuest, vector<Answer>& vecAnsw);
void PrintAnswers(vector<Answer>& vecA, vector<Answer>& AnswForQ, size_t QIndex);
void DeleteQuestion(vector<Question>& vecQuest, vector<Answer>& vecAnsw);
void FindInfo(vector<Question>& vecQuest, vector<Answer>& vecAnsw, vector<Person>& vecPerson, vector<Relation>& vecRelation);


int main()
{
	vector<Question> vecQuest;
	vector<Answer> vecAnsw;
	vector<Person> vecPerson;
	vector<Relation> vecRelation;

	Question::FromBinToVec(vecQuest, MaxQIndex);
	Answer::FromBinToVec(vecAnsw, MaxAIndex);
	Person::FromBinToVec(vecPerson, MaxPIndex);
	Relation::FromBinToVec(vecRelation, MaxRIndex);


	MainMenu();
	while (state != 0)
	{
		switch (state)
		{
		case 1:
			Test(vecQuest, vecAnsw, vecPerson, vecRelation);
			break;
		case 2:
			FindInfo(vecQuest, vecAnsw, vecPerson, vecRelation);
			break;
		case 3:
			AddNewQuestion(vecQuest, vecAnsw);
			break;
		case 4:
			DeleteQuestion(vecQuest, vecAnsw);
			break;
		default:
			break;
		}
	}
	return 0;
}	

void MainMenu()
{
	system("cls");
	cout << "Menu\n"
		<< "(0)Exit\n"
		<< "(1)Test\n"
		<< "(2)Find info\n"
		<< "(3)Add new question\n"
		<< "(4)Delete question\n";

	cin >> state;
}

void PrintQuestions(vector<Question>& vecQ)
{
	for (size_t i = 0; i < vecQ.size(); i++)
	{
		cout << "(" << i + 1 << ")";
		vecQ[i].PrintQuest();
	}
}

void PrintAnswers(vector<Answer>& vecA, vector<Answer>& AnswForQ, size_t QIndex)
{
	int counter = 1;

	cout << "(0)Exit\n";
	for (size_t i = 0; i < vecA.size(); i++)
		if (QIndex == vecA[i].GetQuestIndex())
		{
			AnswForQ.push_back(vecA[i]);
			cout << "(" << counter++ << ")";
			vecA[i].PrintAnswer();
		}
}

void Test(vector<Question>& vecQuest, vector<Answer>& vecAnsw, vector<Person>& vecPerson, vector<Relation>& vecRelation)
{
	bool end = false;
	string Name;
	int EnterQuestion;

	system("cls");
	cout << "Enter your name\n";
	std::getline(std::cin >> std::ws, Name);
	Person NewPer(Name.c_str(), MaxPIndex);
	vecPerson.push_back(NewPer);
	size_t PerIndex = NewPer.GetIndex();
	Person::FromVecToBin(vecPerson, MaxPIndex);

	while (!end)
	{
		system("cls");
		cout << "Questions:\n" << "(0)Exit\n";
		PrintQuestions(vecQuest);
		cout << "Enter number of question\n";
		cin >> EnterQuestion;
		EnterQuestion--;
		if (EnterQuestion >= 0 && EnterQuestion < vecQuest.size())
		{
			int EnterAnswer = 0;
			int QuestIndex;
			bool end = false;
			vector<Answer> AnswForQ;

			system("cls");
			vecQuest[EnterQuestion].PrintQuest();
			cout << "Choose one or more answers, then enter \"0\"\n";
			QuestIndex = vecQuest[EnterQuestion].GetIndex();
			PrintAnswers(vecAnsw, AnswForQ, vecQuest[EnterQuestion].GetIndex());
			if (AnswForQ.size() == 0)
			{
				cout << "Answers for this question is not exist\n";
				char pause = _getch();
			}
			else
			{
				cin >> EnterAnswer;
				EnterAnswer--;
			}
			if (EnterAnswer >= 0 && EnterAnswer < AnswForQ.size())
			{
				while (EnterAnswer >= 0 && EnterAnswer < AnswForQ.size() && AnswForQ.size() != 0)
				{
					size_t AnswIndex = AnswForQ[EnterAnswer].GetIndex();
					Relation NewRel(PerIndex, QuestIndex, AnswIndex, MaxRIndex);
					vecRelation.push_back(NewRel);
					Relation::FromVecToBin(vecRelation, MaxRIndex);
					AnswForQ.erase(AnswForQ.begin() + EnterAnswer);

					system("cls");
					vecQuest[EnterQuestion].PrintQuest();
					cout << "Choose one or more answers, then enter \"0\"\n";
					cout << "(0)Stop\n";
					for (size_t i = 0; i < AnswForQ.size(); i++)
					{
						cout << "(" << i + 1 << ")";
						AnswForQ[i].PrintAnswer();
					}
					cin >> EnterAnswer;
					EnterAnswer--;
				}

				cout << "Thank you for testing!\n";
				char pause = _getch();
			}
		}
		else
			end = true;
	}
	MainMenu();
}

void AddNewQuestion(vector<Question>& vecQuest, vector<Answer>& vecAnsw)
{
	system("cls");
	cout << "Enter new question\n";
	string quest;
	std::getline(std::cin >> std::ws, quest);
	Question NewQuest(quest.c_str(), MaxQIndex);
	vecQuest.push_back(NewQuest);

	system("cls");
	cout << "Enter answers for this question, then enter \"0\"\n";
	string answ;
	std::getline(std::cin >> std::ws, answ);
	while (answ != "0")
	{
		int QIndex = NewQuest.GetIndex();
		Answer NewAnsw(answ.c_str(), QIndex, MaxAIndex);
		vecAnsw.push_back(NewAnsw);
		std::getline(std::cin >> std::ws, answ);
	}
	Question::FromVecToBin(vecQuest, ::MaxQIndex);

	Answer::FromVecToBin(vecAnsw, ::MaxAIndex);

	cout << "Your question is successfuly added\n";
	char pause = _getch();
	MainMenu(); 
}

void DeleteQuestion(vector<Question>& vecQuest, vector<Answer>& vecAnsw)
{
	int EnterQuestion;

	system("cls");
	cout << "Questions:\n" << "(0)Exit\n";
	PrintQuestions(vecQuest);
	cout << "Enter number of question:\n";
	cin >> EnterQuestion;
	EnterQuestion--;

	system("cls");
	if (EnterQuestion >= 0 && EnterQuestion < vecQuest.size())
	{
		int state;

		system("cls");
		vecQuest[EnterQuestion].PrintQuest();
		cout << "(0)Exit\n" << "(1)Delete question\n" << "(2)Delete answer for this question\n";
		cin >> state;
		if (state == 1)
		{
			int Qindex = vecQuest[EnterQuestion].GetIndex();
			vecQuest.erase(vecQuest.begin() + EnterQuestion);
			for (size_t i = 0; i < vecAnsw.size(); i++)
			{
				if(vecAnsw[i].GetQuestIndex() == Qindex)
					vecAnsw.erase(vecAnsw.begin() + i);
			}

			Question::FromVecToBin(vecQuest, MaxQIndex);
			Answer::FromVecToBin(vecAnsw, MaxAIndex);

			system("cls");
			cout << "Your question is successfully deleted\n";
			char pause = _getch();
		}
		else if (state == 2)
		{
			int VecSize;
			int EnterAnswer;
			vector<Answer> AnswForQ;

			system("cls");
			vecQuest[EnterQuestion].PrintQuest();
			PrintAnswers(vecAnsw, AnswForQ, vecQuest[EnterQuestion].GetIndex());
			VecSize = AnswForQ.size();
			cin >> EnterAnswer;
			EnterAnswer--;
			if (EnterAnswer >= 0 && EnterAnswer < VecSize)
			{

				for (size_t i = 0; i < vecAnsw.size(); i++)
				{
					if (vecAnsw[i].GetIndex() == AnswForQ[EnterAnswer].GetIndex())
					{
						vecAnsw.erase(vecAnsw.begin() + i);
						ofstream WriteAVecToBin("AnswerBase", ios::binary | ios::out);
						Answer::FromVecToBin(vecAnsw, MaxAIndex);
						WriteAVecToBin.close();
						break;
					}
				}
			}
			system("cls");
			cout << "Your answer is successfully deleted\n";
			char pause = _getch();
		}
	}
	MainMenu();
}

void FindInfo(vector<Question>& vecQuest, vector<Answer>& vecAnsw, vector<Person>& vecPerson, vector<Relation>& vecRelation)
{
	int input;

	system("cls");
		bool pex = false;
		bool qex = false;
		bool aex = false;
		size_t PIndex;
		vector<Answer> answers;
		vector<bool> printq;

		cout << "Input name\n";
		string name;
		std::getline(std::cin >> std::ws, name);
		system("cls");
		for (size_t i = 0; i < vecPerson.size(); i++)
		{
			if (name == vecPerson[i].GetName())
			{
				pex = true;
				PIndex = vecPerson[i].GetIndex();
				cout << "\t" << name << "(" << vecPerson[i].GetIndex() << "):" << endl << endl;
				for (size_t j = 0; j < vecRelation.size(); j++)
				{
					if (PIndex == vecRelation[j].GetPIndex())
					{
						size_t QIndex = vecRelation[j].GetQIndex();
						size_t AIndex = vecRelation[j].GetAIndex();
						for (size_t k = 0; k < vecQuest.size(); k++)
						{
							if (QIndex == vecQuest[k].GetIndex())
							{
								qex = true;
								vecQuest[k].PrintQuest();
								for (size_t m = 0; m < vecAnsw.size(); m++)
								{
									if (AIndex == vecAnsw[m].GetIndex())
									{
										aex = true;
										vecAnsw[m].PrintAnswer();
										cout << endl;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
		if (!pex)
		{
			cout << "Person is not exist\n";
		}
		else if (!qex)
		{
			cout << "Questions is not exist\n";
		}
		else if (!aex)
		{
			cout << "Answers is not exist\n";
		}

		char stop = _getch();
	MainMenu();
} 

//for (size_t i = 0; i < vecPerson.size(); i++)
//{
//	if (name == vecPerson[i].GetName())
//	{
//		pex = true;
//		PIndex = vecPerson[i].GetIndex();
//		cout << "\t" << name << "(" << vecPerson[i].GetIndex() << "):" << endl << endl;
//		for (size_t j = 0; j < vecRelation.size(); j++)
//		{
//			if (PIndex == vecRelation[j].GetPIndex())
//			{
//				size_t QIndex = vecRelation[j].GetQIndex();
//				size_t AIndex = vecRelation[j].GetAIndex();
//				for (size_t k = 0; k < vecQuest.size(); k++)
//				{
//					if (QIndex == vecQuest[k].GetIndex())
//					{
//						qex = true;
//						vecQuest[k].PrintQuest();
//						for (size_t m = 0; m < vecAnsw.size(); m++)
//						{
//							if (AIndex == vecAnsw[m].GetIndex())
//							{
//								aex = true;
//								vecAnsw[m].PrintAnswer();
//								cout << endl;
//								break;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}