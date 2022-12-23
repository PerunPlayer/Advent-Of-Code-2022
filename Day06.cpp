#include <iostream>
#include <deque>

using namespace std;

bool checkMarker(deque<char>& marker);

int main()
{
	char input;
	deque<char> marker;
	uint64_t processed = 0;
	
	//start-of-packet marker consists of 4 distinct characters - TASK 1
	//const size_t markerLength = 4;
	//start-of-message marker consists of 14 distinct characters - TASK 2
	const size_t markerLength = 14;

	while (true)
	{
		cin.get(input);
		if ((input == ' ') || (input == '\n'))
		{
			break;
		}

		processed++;
		if (marker.size() < markerLength)
		{
			marker.push_back(input);
			continue;
		}
		marker.pop_front();
		marker.push_back(input);

		if ((marker.size() > (markerLength - 1)) && checkMarker(marker))
		{
			break;
		}
	}

	cout << "Processed characters until marker detected: " << processed << endl;

	return 0;
}

bool checkMarker(deque<char>& marker)
{
	for (size_t i = 0; i < marker.size(); i++)
	{
		for (size_t j = i + 1; j < marker.size(); j++)
		{
			if (marker[i] == marker[j])
			{
				return false;
			}
		}
	}

	return true;
}
