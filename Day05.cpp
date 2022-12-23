#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <tuple>

using namespace std;

void executeInstructionsWithOldCrane(string input, vector<stack<char>>& stacks);
void executeInstructionsWithNewCrane(string input, vector<stack<char>>& stacks);
tuple<int, int, int> extractCoordinatesFromString(string input);
string getFinalState(vector<stack<char>>& stacks);
vector<stack<char>> hardcode();

int main()
{
	string input;
	bool isEnd = false;
	vector<stack<char>> stacks = hardcode();

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

		//CrateMover 9000 is moving 1 crate at a time
		//CrateMover 9001 is moving multiple crates at once
		executeInstructionsWithOldCrane(input, stacks); //TASK 1
		executeInstructionsWithNewCrane(input, stacks); //TASK 2
	}

	cout << "Top crates ends up: " << getFinalState(stacks) << endl;
	cout << "" << endl;

	return 0;
}

/*TASK 1*/
void executeInstructionsWithOldCrane(string input, vector<stack<char>>& stacks)
{
	auto coordinates = extractCoordinatesFromString(input);
	for (size_t i = 0; i < get<0>(coordinates); i++)
	{
		char crate = stacks[get<1>(coordinates)].top();
		stacks[get<1>(coordinates)].pop();
		stacks[get<2>(coordinates)].push(crate);
	}
}

/*TASK 2*/
void executeInstructionsWithNewCrane(string input, vector<stack<char>>& stacks)
{
	auto coordinates = extractCoordinatesFromString(input);
	stack<char> craneContainer;
	size_t cratesCountToMove = get<0>(coordinates);
	for (size_t i = 0; i < cratesCountToMove; i++)
	{
		char crate = stacks[get<1>(coordinates)].top();
		craneContainer.push(crate);
		stacks[get<1>(coordinates)].pop();
	}
	for (size_t i = 0; i < cratesCountToMove; i++)
	{
		char crate = craneContainer.top();
		stacks[get<2>(coordinates)].push(crate);
		craneContainer.pop();
	}
}

tuple<int, int, int> extractCoordinatesFromString(string input)
{
	string buffer;
	size_t i = 5; // skipping "move "
	while (input[i] != ' ')
	{
		buffer.push_back(input[i]);
		i++;
	}
	int iterations = stoi(buffer);

	i += 6; // skipping " from "
	buffer.clear();
	while (input[i] != ' ')
	{
		buffer.push_back(input[i]);
		i++;
	}
	int sourceStack = stoi(buffer);

	i += 4; // skipping " to "
	buffer.clear();
	while (input[i] != '\0')
	{
		buffer.push_back(input[i]);
		i++;
	}
	int destinationStack = stoi(buffer);
	return make_tuple(iterations, sourceStack - 1, destinationStack - 1);
}

string getFinalState(vector<stack<char>>& stacks)
{
	string finalState;
	for (stack<char> stack : stacks)
	{
		finalState.push_back(stack.top());
	}

	return finalState;
}

vector<stack<char>> hardcode()
{
	vector<stack<char>> stacks;
	stack<char> supplies;
	supplies.push('F');
	supplies.push('H');
	supplies.push('B');
	supplies.push('V');
	supplies.push('R');
	supplies.push('Q');
	supplies.push('D');
	supplies.push('P');
	stacks.push_back(supplies);

	supplies = stack<char>();
	supplies.push('L');
	supplies.push('D');
	supplies.push('Z');
	supplies.push('Q');
	supplies.push('W');
	supplies.push('V');
	stacks.push_back(supplies);

	supplies = stack<char>();
	supplies.push('H');
	supplies.push('L');
	supplies.push('Z');
	supplies.push('Q');
	supplies.push('G');
	supplies.push('R');
	supplies.push('P');
	supplies.push('C');
	stacks.push_back(supplies);

	supplies = stack<char>();
	supplies.push('R');
	supplies.push('D');
	supplies.push('H');
	supplies.push('F');
	supplies.push('J');
	supplies.push('V');
	supplies.push('B');
	stacks.push_back(supplies);

	supplies = stack<char>();
	supplies.push('Z');
	supplies.push('W');
	supplies.push('L');
	supplies.push('C');
	stacks.push_back(supplies);

	supplies = stack<char>();
	supplies.push('J');
	supplies.push('R');
	supplies.push('P');
	supplies.push('N');
	supplies.push('T');
	supplies.push('G');
	supplies.push('V');
	supplies.push('M');
	stacks.push_back(supplies);

	supplies = stack<char>();
	supplies.push('J');
	supplies.push('R');
	supplies.push('L');
	supplies.push('V');
	supplies.push('M');
	supplies.push('B');
	supplies.push('S');
	stacks.push_back(supplies);

	supplies = stack<char>();
	supplies.push('D');
	supplies.push('P');
	supplies.push('J');
	stacks.push_back(supplies);

	supplies = stack<char>();
	supplies.push('D');
	supplies.push('c');
	supplies.push('N');
	supplies.push('W');
	supplies.push('V');
	stacks.push_back(supplies);

	return stacks;
}
