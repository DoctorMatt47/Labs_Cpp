#include <iostream>
#include <string>
#include <list>
#include "ExTree.h"

using namespace std;

bool isOperation(char ch);
void delSpaces(string& exp);
void NodesToTree(list<Node*>& listNode);
void strToList(string exp, list<Node*>& list);

int main()
{
	ExTree et;
	string exp;
	list<Node*> listNode;
	std::cout << "Enter expression:\n";

	std::getline(std::cin, exp);
	std::cout << endl;

	delSpaces(exp);
	strToList(exp, listNode);

	NodesToTree(listNode);

	et.setRoot(*listNode.begin());

	et.printTree();

	int result = et.evaluate();
	std::cout << "Result: " << result << endl;

	return 0;
}

void delSpaces(string& exp)
{
	for (size_t i = 0; i < exp.size(); i++)
	{
		if(exp[i] == ' ')
			exp.erase(exp.begin() + i);
	}
}

void strToList(string exp, list<Node*>& list)
{
	size_t lastOper = 0;
	string lastNum;
	for (size_t i = 0; i < exp.size(); i++)
	{
		if (isOperation(exp[i]))
		{
			lastOper = i;
			string numLeft;
			string oper;
			oper = exp[i];
			int j = i - 1;
			while (j >= 0 && !isOperation(exp[j]))
			{
				numLeft = exp[j] + numLeft;
				j--;
			}
			if (numLeft.size() != 0)
			{
				Node* node1 = new Node(numLeft);
				list.push_back(node1);
			}
			Node* node2 = new Node(oper);
			list.push_back(node2);
		}
	}
	for (size_t k = lastOper + 1; k < exp.size(); k++)
	{
		lastNum += exp[k];
	}
	Node* node3 = new Node(lastNum);
	list.push_back(node3);
}

bool isOperation(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%')
	{
		return true;
	}
	return false;
}

void NodesToTree(list<Node*>& listNode)
{
	for (auto i = listNode.begin(); i != listNode.end(); i++)
	{
		if ((*i)->getData() == "-" && (i == listNode.begin() || (*prev(i))->isOperation()))
		{
			(*i)->setRight(*next(i));
			listNode.erase(next(i));
		}
	}
	for (auto i = listNode.begin(); i != listNode.end(); i++)
	{
		if ((*i)->getData() == "^")
		{
			(*i)->setLeft(*prev(i));
			(*i)->setRight(*next(i));
			listNode.erase(prev(i));
			listNode.erase(next(i));
		}
	}
	for (auto i = listNode.begin(); i != listNode.end(); i++)
	{
		if ((*i)->getData() == "*" || (*i)->getData() == "/" || (*i)->getData() == "%")
		{
			(*i)->setLeft(*prev(i));
			(*i)->setRight(*next(i));
			listNode.erase(prev(i));
			listNode.erase(next(i));
		}
	}
	for (auto i = listNode.begin(); i != listNode.end(); i++)
	{
		if ((*i)->getData() == "+" || (*i)->getData() == "-")
		{
			(*i)->setLeft(*prev(i));
			(*i)->setRight(*next(i));
			listNode.erase(prev(i));
			listNode.erase(next(i));
		}
	}
}