#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

uint64_t calculateRoundByInput(char opponent, char ownAction);
uint64_t calculateRoundByEnding(char opponent, char ending);

int main()
{
	std::string input;
	bool isEnd = false;
	uint64_t points = 0;

	while (true)
	{
		getline(cin, input);
		if (input.empty() && !isEnd)
		{
			isEnd = true;
			continue;
		}
		else if (input.empty() && isEnd)
		{
			break;
		}

		isEnd = false;
		//points += calculateRoundByInput(input[0], input[2]); //TASK 1
		points += calculateRoundByEnding(input[0], input[2]); //TASK 2
	}

	cout << "Total points from the tournament: " << points << endl;
	return 0;
}

/*TASK 1*/
uint64_t calculateRoundByInput(char opponent, char ownAction)
{
	uint64_t result = 0;

	switch (ownAction)
	{
	case 'X': result += 1;
		switch (opponent)
		{
		case 'A': result += 3;
			break;
		case 'B': break;
		case 'C': result += 6;
			break;
		}
		break;
	case 'Y': result += 2;
		switch (opponent)
		{
		case 'A': result += 6;
			break;
		case 'B': result += 3;
			break;
		case 'C': break;
		}
		break;
	case 'Z': result += 3;
		switch (opponent)
		{
		case 'A': break;
		case 'B': result += 6;
			break;
		case 'C': result += 3;
			break;
		}
		break;
	}

	return result;
}

/*TASK 2*/
uint64_t calculateRoundByEnding(char opponent, char ending)
{
	uint64_t result = 0;

	switch (ending)
	{
	case 'X':
		switch (opponent)
		{
		case 'A': result += 3;
			break;
		case 'B': result += 1;
			break;
		case 'C': result += 2;
			break;
		}
		break;
	case 'Y': result += 3;
		switch (opponent)
		{
		case 'A': result += 1;
			break;
		case 'B': result += 2;
			break;
		case 'C': result += 3;
			break;
		}
		break;
	case 'Z': result += 6;
		switch (opponent)
		{
		case 'A': result += 2;
			break;
		case 'B': result += 3;
			break;
		case 'C': result += 1;
			break;
		}
		break;
	}

	return result;
}