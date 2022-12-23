#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

int main()
{
	vector<vector<uint64_t>> inventories;
	vector<uint64_t> singleInventory;
	string input;
	bool isEnd = false;

	/*INPUT*/
	while(true)
	{
		getline(cin, input);
		if (input.empty() && !isEnd)
		{
			isEnd = true;
			if (!singleInventory.empty())
			{
				inventories.push_back(singleInventory);
				singleInventory.clear();
			}
			continue;
		}
		else if (input.empty() && isEnd)
		{
			break;
		}
		
		isEnd = false;
		singleInventory.push_back(stoi(input));
	}

	//TASK 1
	/*FINDING TOP ELF*/
	int biggestInventory = 0, position = 0, curr = 0;
	uint64_t wholeTrail = 0;
	for (vector<uint64_t> inventory : inventories)
	{
		int buffer = 0;
		for (int item : inventory)
		{
			buffer += item;
		}
		if (buffer > biggestInventory)
		{
			biggestInventory = buffer;
			position = curr;
		}
		wholeTrail += buffer;
		curr++;
	}

	cout << "The biggest inventory contains: " << biggestInventory << " calories and is carried by elf: " << position + 1 << ".\n";
	cout << "The whole trail carries: " << wholeTrail << " calories.\n";

	//TASK 2
	/*FINDING TOP 3 ELVES*/
	vector<int> topElvesInventories;
	topElvesInventories.push_back(0);
	topElvesInventories.push_back(0);
	topElvesInventories.push_back(0);
	for (vector<uint64_t> inventory : inventories)
	{
		int buffer = 0;
		for (int item : inventory)
		{
			buffer += item;
		}
		if (buffer > topElvesInventories[0])
		{
			topElvesInventories[2] = topElvesInventories[1];
			topElvesInventories[1] = topElvesInventories[0];
			topElvesInventories.insert(topElvesInventories.begin(), buffer);
		}
		else if(buffer > topElvesInventories[1])
		{
			topElvesInventories[2] = topElvesInventories[1];
			topElvesInventories.insert(topElvesInventories.begin() + 1, buffer);
		}
		else if (buffer > topElvesInventories.back())
		{
			topElvesInventories.back() = buffer;
		}
	}

	int topSum = topElvesInventories[0] + topElvesInventories[1] + topElvesInventories[2];

	cout << "The top 3 elves are carrying: " << topSum << " calories.\n";

	return 0;
}