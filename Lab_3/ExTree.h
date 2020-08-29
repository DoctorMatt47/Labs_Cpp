#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node
{
	friend class ExTree;
private:
	string data;
	Node* pLeft;
	Node* pRight;

public:

	Node(string data = string());

	string getData();

	void setLeft(Node* node);

	void setRight(Node* node);

	bool isOperation();

	bool isArg(Node* node);

	int toNum(string data, vector<std::pair<string, int>>& parameters);
};

class ExTree : public Node
{
private:

	Node* root;

	vector<std::pair<string, int>> parameters;

	void deleteTree(Node* node);

	void printTree(const std::string& prefix, const Node* node, bool isLeft);

	int evaluate(Node* root);

public:

	ExTree();

	~ExTree();

	void setRoot(Node* root);

	void printTree();

	int evaluate();
};

