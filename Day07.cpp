#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Element
{
	string name;
	uint64_t size;
	bool isDirectory;
	Element() : name(), size(0), isDirectory(false) {}
	Element(string& _name, uint64_t _size, bool _isDirectory)
		: name(_name), size(_size), isDirectory(_isDirectory) {}
	Element(const string& _name, uint64_t _size, bool _isDirectory)
		: name(_name), size(_size), isDirectory(_isDirectory) {}
};

template <class T>
struct TreeNode
{
	T data;
	vector<TreeNode> children;
	TreeNode* parent;
	TreeNode(const T& _data) : data(_data), parent(nullptr) {}
	TreeNode(const T& _data, TreeNode* _parent) : data(_data), parent(_parent) {}
};

void parseInput(string input, TreeNode<Element>*& currentPosition, TreeNode<Element>*& root);
vector<string> splitString(string input, char symbol);
void addChild(vector<string> splittedInput, TreeNode<Element>*& currentPosition);
void executeCommand(vector<string> splittedInput, TreeNode<Element>*& currentPosition, TreeNode<Element>*& root);
size_t calculate(TreeNode<Element>*& root, size_t& totalSize, const size_t MAX_SIZE);
void calculateDeviseUsedSpace(TreeNode<Element>*& root, size_t& usedSpace);
void getSmallestFolderAboveRequestedSpace(TreeNode<Element>*& root, const size_t& spaceToDelete, size_t& minSize);

int main()
{
	string input;
	bool isEnd = false;
	size_t totalSize = 0;
	Element rootData("root", 0, true);
	TreeNode<Element>* root = new TreeNode<Element>(rootData);
	auto currentPosition = root;

	while (true)
	{
		getline(cin, input);
		if (input.empty())
		{
			if (!isEnd)
			{
				isEnd = true;
				continue;
			}
			break;
		}

		isEnd = false;
		parseInput(input, currentPosition, root);
	}

	/*TASK 1*/
	const size_t MAX_SIZE = 100000;
	calculate(root, totalSize, MAX_SIZE);

	/*TASK 2*/
	const size_t SIZE_OF_DEVICE = 70000000;
	const size_t SIZE_OF_UPDATE = 30000000;
	size_t usedSpace = 0;
	calculateDeviseUsedSpace(root, usedSpace);
	size_t minSize = -1;
	const size_t spaceToDelete = ((SIZE_OF_DEVICE - usedSpace) < SIZE_OF_UPDATE) ? (SIZE_OF_UPDATE - (SIZE_OF_DEVICE - usedSpace)) : 0;
	getSmallestFolderAboveRequestedSpace(root, spaceToDelete, minSize);

	cout << "Total size: " << totalSize << endl; //TASK 1
	cout << "Deleted folder size: " << minSize << endl; //TASK 2

	return 0;
}

void parseInput(string input, TreeNode<Element>*& currentPosition, TreeNode<Element>*& root)
{
	vector<string> splittedInput = splitString(input, ' ');
	if (splittedInput[0] == "$")
	{
		executeCommand(splittedInput, currentPosition, root);
	}
	else
	{
		addChild(splittedInput, currentPosition);
	}
}

vector<string> splitString(string input, char symbol)
{
	size_t splitPosition;
	vector<string> splitted;
	for (size_t i = 0; i < input.size();)
	{
		splitPosition = input.find(' ', i);
		string newString = input.substr(i, splitPosition - i);
		splitted.push_back(newString);
		i += newString.size() + 1;
	}

	return splitted;
}

void addChild(vector<string> splittedInput, TreeNode<Element>*& currentPosition)
{
	Element newData;
	if (splittedInput[0] == "dir")
	{
		newData.name = splittedInput[1];
		newData.size = 0;
		newData.isDirectory = true;
	}
	else
	{
		newData.name = splittedInput[1];
		newData.size = stoi(splittedInput[0]);
		newData.isDirectory = false;
	}

	TreeNode<Element>* newChild = new TreeNode<Element>(newData, currentPosition);
	currentPosition->children.push_back(*newChild);
}

void executeCommand(vector<string> splittedInput, TreeNode<Element>*& currentPosition, TreeNode<Element>*& root)
{
	if (splittedInput[1] == "cd")
	{
		if (splittedInput[2] == "..")
		{
			currentPosition = currentPosition->parent;
		}
		else if (splittedInput[2] == "/")
		{
			currentPosition = root;
		}
		else
		{
			string name = splittedInput[2];
			for (size_t i = 0; i < currentPosition->children.size(); i++)
			{
				if (currentPosition->children[i].data.name == name)
				{
					currentPosition = &currentPosition->children[i];
					return;
				}
			}
		}
	}
}

size_t calculate(TreeNode<Element>*& root, size_t& totalSize, const size_t MAX_SIZE)
{
	if (!root || !root->data.isDirectory)
	{
		return 0;
	}

	size_t size = 0;
	for (TreeNode<Element> child : root->children)
	{
		if (child.data.isDirectory)
		{
			TreeNode<Element>* childToCheck = &child;
			size += calculate(childToCheck, totalSize, MAX_SIZE);
			child.data.size = size;
		}
		else
		{
			size += child.data.size;
		}
	}

	if (size <= MAX_SIZE)
	{
		totalSize += size;
	}
	return size;
}

void calculateDeviseUsedSpace(TreeNode<Element>*& root, size_t& usedSpace)
{
	if (!root || !root->data.isDirectory)
	{
		return;
	}

	for (size_t i = 0; i < root->children.size(); i++)
	{
		if (root->children[i].data.isDirectory)
		{
			TreeNode<Element>* childToCheck = &root->children[i];
			calculateDeviseUsedSpace(childToCheck, usedSpace);
		}
		else
		{
			usedSpace += root->children[i].data.size;
		}
		root->data.size += root->children[i].data.size;
	}
}

void getSmallestFolderAboveRequestedSpace(TreeNode<Element>*& root, const size_t& spaceToDelete, size_t& minSize)
{
	if (!root || !root->data.isDirectory)
	{
		return;
	}

	for (TreeNode<Element> child : root->children)
	{
		TreeNode<Element>* childToCheck = &child;
		getSmallestFolderAboveRequestedSpace(childToCheck, spaceToDelete, minSize);
		if ((child.data.size > spaceToDelete) && (child.data.size < minSize))
		{
			minSize = child.data.size;
		}
	}
}
