#include <iostream>
#include <string>
#include <vector>

using namespace std;

pair<string, int> parseInput(const string input);
void executeTick(vector<pair<short, int>>& buffer, int& cpuRegister, size_t& tick);
void drawPixel(int cpuRegister, vector<vector<char>>& screen, const size_t tick, int& currentRow, int& currentColl, bool isFirstTime = false);

int main()
{
	string input;
	int cpuRegister = 1;
	vector<pair<short, int>> buffer;
	int signalStrengths = 0, currentRow = 0, currentColl = 0;
	size_t tick = 1;
	pair<string, int> command("", 0);
	vector<vector<char>> screen;
	vector<char> row(40);
	for (size_t i = 0; i < 6; i++)
	{
		screen.push_back(row);
	}
	bool skip = false;

	while (true)
	{
		getline(cin, input);
		if (input.empty())
		{
			break;
		}

		command = parseInput(input);

		if (command.second)
		{
			short ticksUntilAdding = 2;
			buffer.push_back(make_pair(ticksUntilAdding, command.second));
		}

		executeTick(buffer, cpuRegister, tick);
		drawPixel(cpuRegister, screen, tick - 1, currentRow, currentColl, true); //TASK 2
		if ((tick >= 20) && (((tick - 20) % 40) == 0))
		{
			signalStrengths += (tick * cpuRegister);
		}

		if (command.second)
		{
			drawPixel(cpuRegister, screen, tick - 1, currentRow, currentColl); //TASK 2
			executeTick(buffer, cpuRegister, tick);

			if ((tick >= 20) && (((tick - 20) % 40) == 0))
			{
				signalStrengths += (tick * cpuRegister);
			}
		}
	}

	cout << "Sum of the signal strengths is " << signalStrengths << "." << endl;

	for (size_t i = 0; i < screen.size(); i++)
	{
		for (size_t j = 0; j < screen[i].size(); j++)
		{
			cout << screen[i][j];
		}
		cout << endl;
	}

	return 0;
}

pair<string, int> parseInput(const string input)
{
	pair<string, int> command("", 0);
	if (input.size() > 4)
	{
		int spacePosition = input.find(' ');
		command.first = input.substr(0, spacePosition);
		command.second = stoi(input.substr(spacePosition + 1, input.size() - spacePosition));
	}
	else
	{
		command.first = input;
	}

	return command;
}

void executeTick(vector<pair<short, int>>& buffer, int& cpuRegister, size_t& tick)
{
	for (size_t i = 0; i < buffer.size(); i++)
	{
		buffer[i].first--;
		if (buffer[i].first == 0)
		{
			cpuRegister += buffer[i].second;
			vector<pair<short, int>>::iterator it = buffer.begin() + i;
			buffer.erase(it);
			i--;
		}
	}

	tick++;
}

void drawPixel(int cpuRegister, vector<vector<char>>& screen, const size_t tick, int& currentRow, int& currentColl, bool isFirstTime)
{
	if ((currentRow >= screen.size()) || currentColl >= screen[currentRow].size())
	{
		return;
	}
	if (cpuRegister < 0 && isFirstTime)
	{
		cpuRegister = 0;
	}

	if ((currentColl == cpuRegister - 1) || (currentColl == cpuRegister) || (currentColl == cpuRegister + 1))
	{
		if ((cpuRegister >= 1) && (screen[currentRow][cpuRegister - 1] != '#') && (screen[currentRow][cpuRegister - 1] != '.'))
		{
			screen[currentRow][cpuRegister - 1] = '#';
		}
		else if ((cpuRegister >= 0) && (screen[currentRow][cpuRegister] != '#') && (screen[currentRow][cpuRegister] != '.'))
		{
			screen[currentRow][cpuRegister] = '#';
		}
		else if ((cpuRegister < screen[currentRow].size() - 1) && (screen[currentRow][cpuRegister + 1] != '#') && (screen[currentRow][cpuRegister + 1] != '.'))
		{
			screen[currentRow][cpuRegister + 1] = '#';
		}
	}
	else
	{
		screen[currentRow][currentColl] = '.';
	}

	currentColl++;
	if (currentColl > 39)
	{
		currentColl = 0;
		currentRow++;
	}
}
