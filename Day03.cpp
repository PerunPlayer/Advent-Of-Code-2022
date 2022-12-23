#include <iostream>
#include <string>

using namespace std;

size_t getSharedItemPriority(string input);
size_t getGroupBadgePriority(string line1, string line2, string line3);

int main()
{
	std::string input;
	bool isEnd = false;
	size_t itemPriority = 0, badgePriority = 0;

	/*TASK 1*/
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
		itemPriority += getSharedItemPriority(input);
	}

	cout << "Total priority is: " << itemPriority << endl;

	/*TASK 2*/
	string line1, line2, line3;
	short counter = 0;
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
		switch (counter)
		{
		case 0: 
			line1 = input;
			counter++;
			break;
		case 1: 
			line2 = input;
			counter++;
			break;
		case 2: 
			line3 = input;
			badgePriority += getGroupBadgePriority(line1, line2, line3);
			counter = 0;
			break;
		}
	}

	cout << "Total badge priority is: " << badgePriority << endl;
	return 0;
}

/*TASK 1*/
size_t getSharedItemPriority(string input)
{
	size_t priority = 0;
	string firstHalf = input.substr(0, input.size() / 2),
		secondHalf = input.substr(input.size() / 2, input.size() / 2);

	for (size_t i = 0; i < firstHalf.size(); i++)
	{
		if (secondHalf.find(firstHalf[i]) == string::npos)
		{
			continue;
		}
		size_t position = secondHalf.find(firstHalf[i]);
		int priorityBonus = (secondHalf[position] >= 'a' && secondHalf[position] <= 'z') ? -96 : -38;
		return size_t(secondHalf[position]) + priorityBonus;
	}
}

/*TASK 2*/
size_t getGroupBadgePriority(string line1, string line2, string line3)
{
	size_t priority = 0;

	for (size_t i = 0; i < line1.size(); i++)
	{
		if ((line2.find(line1[i]) == string::npos) || (line3.find(line1[i]) == string::npos))
		{
			continue;
		}
		size_t position = line2.find(line1[i]);
		int priorityBonus = (line2[position] >= 'a' && line2[position] <= 'z') ? -96 : -38;
		return size_t(line2[position]) + priorityBonus;
	}
}
