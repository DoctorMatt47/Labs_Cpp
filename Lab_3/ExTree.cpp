#include "ExTree.h"

ExTree::ExTree()
{
	root = nullptr;
}

ExTree::~ExTree()
{
	Node* node = root;
	if (node != nullptr)
	{
		deleteTree(node->pLeft);
		deleteTree(node->pRight);

		delete node;
	}
}

void ExTree::setRoot(Node* root)
{
	this->root = root;
}

void ExTree::printTree(const std::string& prefix, const Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		if (isLeft)
			std::cout << "|__";
		else
			std::cout << "\\__";

		std::cout << "'" << node->data << "'" << std::endl;

		printTree(prefix + (isLeft ? "|   " : "    "), node->pLeft, true);
		printTree(prefix + (isLeft ? "|   " : "    "), node->pRight, false);
	}
}

void ExTree::printTree()
{
	printTree("", root, false);
	cout << endl;
}

int ExTree::evaluate()
{
	parameters.clear();
	return evaluate(root);
}

int ExTree::evaluate(Node* root)
{
	if(!root)
		return 0;

	if (!root->pLeft && !root->pRight)
		return toNum(root->data, parameters);

	int leftVal = evaluate(root->pLeft);

	int rightVal = evaluate(root->pRight);

	if (root->data == "+")
		return leftVal + rightVal;
	if (root->data == "-" && root->pLeft)
		return leftVal - rightVal;
	if (root->data == "-" && !root->pLeft)
		return rightVal * -1;
	if (root->data == "*")
		return leftVal * rightVal;
	if (root->data == "/")
		return leftVal / rightVal;
	if (root->data == "%")
		return leftVal % rightVal;
	if (root->data == "^")
		return pow(leftVal,rightVal);
}

void ExTree::deleteTree(Node* node)
{
	if (node != nullptr)
	{
		deleteTree(node->pLeft);
		deleteTree(node->pRight);
		delete node;
	}
}

Node::Node(string data)
{
	this->data = data;
	pLeft = nullptr;
	pRight = nullptr;
}

string Node::getData()
{
	return data;
}

void Node::setLeft(Node* node)
{
	pLeft = node;
}

void Node::setRight(Node* node)
{
	pRight = node;
}

bool Node::isOperation()
{
	if (data == "+" || data == "-" || data == "*" ||
		data == "/" || data == "^" || data == "%")
		return true;
	else
		return false;
}

bool Node::isArg(Node* node)
{
	for (size_t i = 0; i < node->data.size(); i++)
	{
		if (isalpha(node->data[i]))
			return true;
	}
	return false;
}

int Node::toNum(string data, vector<std::pair<string, int>>& parameters)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (!isdigit(data[i]))
		{
			for (size_t j = 0; j < parameters.size(); j++)
			{
				if (data == parameters[j].first)
				{
					return parameters[j].second;
				}
			}
			int num;
			cout << "Parameter " << data << " = ";
			cin >> num;
			std::pair<string, int> p;
			p.first = data;
			p.second = num;
			parameters.push_back(p);
			return num;
		}
	}
	return atoi(data.c_str());
}
