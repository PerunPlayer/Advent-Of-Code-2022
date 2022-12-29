#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

bool moveTail(pair<int, int>& currentHeadCoordinates, pair<int, int>& currentTailCoordinates);
void moveInDirection(char direction, size_t steps, set<pair<int, int>>& visitedCoordinates, vector<pair<int, int>>& currentCoordinates);

int main()
{
	string input;
	bool isEnd = false;
	set<pair<int, int>> visitedCoordinates;
	char direction;
	size_t steps = 0;
	pair<int, int> currentHeadCoordinates = make_pair(0, 0);

	/*TASK 1*/
	//vector<pair<int, int>> currentCoordinates(2, currentHeadCoordinates);
	/*TASK 2*/
	vector<pair<int, int>> currentCoordinates(10, currentHeadCoordinates);
	
	visitedCoordinates.insert(currentHeadCoordinates);

	while (true)
	{
		getline(cin, input);
		if (input.empty())
		{
			break;
		}

		direction = input[0];
		steps = stoi(input.substr(2, input.size() - 2));

		moveInDirection(direction, steps, visitedCoordinates, currentCoordinates);
	}	

	cout << "Total visited coordinates: " << visitedCoordinates.size() << endl;

	return 0;
}

bool moveTail(pair<int, int>& currentHeadCoordinates, pair<int, int>& currentTailCoordinates)
{
	bool moved = false;
	if ((abs(currentHeadCoordinates.first - currentTailCoordinates.first) > 1) ||
		(abs(currentHeadCoordinates.second - currentTailCoordinates.second) > 1))
	{
		moved = true;
		if (currentHeadCoordinates.first > currentTailCoordinates.first)
		{
			currentTailCoordinates.first += 1;
		}
		else if (currentHeadCoordinates.first < currentTailCoordinates.first)
		{
			currentTailCoordinates.first -= 1;
		}
		if (currentHeadCoordinates.second > currentTailCoordinates.second)
		{
			currentTailCoordinates.second += 1;
		}
		else if (currentHeadCoordinates.second < currentTailCoordinates.second)
		{
			currentTailCoordinates.second -= 1;
		}
	}

	return moved;
}

void moveInDirection(char direction, size_t steps, set<pair<int, int>>& visitedCoordinates, vector<pair<int, int>>& currentCoordinates)
{
	short xMove = 0, yMove = 0;
	switch (direction)
	{
	case 'U': xMove = 1;
		break;
	case 'D': xMove = -1;
		break;
	case 'L': yMove = -1;
		break;
	case 'R': yMove = 1;
		break;
	}

	for (size_t i = 0; i < steps; i++)
	{		
		currentCoordinates[0].first += xMove;
		currentCoordinates[0].second += yMove;
		bool moved = false;
		for (size_t j = 1; j < currentCoordinates.size(); j++)
		{
			moved = moveTail(currentCoordinates[j - 1], currentCoordinates[j]);
			if (!moved)
			{
				break;
			}
		}
		visitedCoordinates.insert(currentCoordinates[currentCoordinates.size() - 1]);
	}
}
