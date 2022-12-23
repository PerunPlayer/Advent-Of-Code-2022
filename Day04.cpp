#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool areFullyOverlappingRegions(string input);
bool areOverlappingRegions(string input);
pair<size_t, size_t> getBounds(string bounds, char symbol);

int main()
{
	string input;
	bool isEnd = false;
	size_t fullyOverlappingRegions = 0, overlappingRegions = 0;

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
		areFullyOverlappingRegions(input) ? fullyOverlappingRegions++ : fullyOverlappingRegions; //TASK 1
		areOverlappingRegions(input) ? overlappingRegions++ : overlappingRegions; //TASK 2
	}

	cout << "Total fully overlapping regions are: " << fullyOverlappingRegions << endl;
	cout << "Total overlapping regions are: " << overlappingRegions << endl;

	return 0;
}

/*TASK 1*/
bool areFullyOverlappingRegions(string input)
{
	size_t charPosition = input.find(',', 0);
	string first = input.substr(0, charPosition),
		   second = input.substr(charPosition + 1, input.size() - charPosition);

	pair<size_t, size_t> firstBounds = getBounds(first, '-');
	pair<size_t, size_t> secondBounds = getBounds(second, '-');

	return (((firstBounds.first <= secondBounds.first) && (firstBounds.second >= secondBounds.second))
		|| ((secondBounds.first <= firstBounds.first) && (secondBounds.second >= firstBounds.second)));
}

/*TASK 2*/
bool areOverlappingRegions(string input)
{
	size_t charPosition = input.find(',', 0);
	string first = input.substr(0, charPosition),
		second = input.substr(charPosition + 1, input.size() - charPosition);

	pair<size_t, size_t> firstBounds = getBounds(first, '-');
	pair<size_t, size_t> secondBounds = getBounds(second, '-');

	return ((firstBounds.first <= secondBounds.first) && (firstBounds.second >= secondBounds.first)
		|| (firstBounds.first <= secondBounds.second) && firstBounds.second >= secondBounds.first);
}

pair<size_t, size_t> getBounds(string boundsStr, char symbol)
{
	size_t charPosition = boundsStr.find('-', 0);
	string lowerBound = boundsStr.substr(0, charPosition),
		   upperBound = boundsStr.substr(charPosition + 1, boundsStr.size() - charPosition);

	pair<size_t, size_t> bounds;
	bounds.first = stoi(lowerBound);
	bounds.second = stoi(upperBound);
	return bounds;
}
