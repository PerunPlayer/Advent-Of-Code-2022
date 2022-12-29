#include <iostream>
#include <string>
#include <vector>

using namespace std; 

void addForestLine(string& input, vector<vector<short>>& forest);
size_t countVisibleTrees(vector<vector<short>>& forest);
size_t getBestTreeVision(vector<vector<short>>& forest);

int main()
{
	string input;
	bool isEnd = false;
	size_t visibleTrees = 0, bestTreeVision = 0;
	vector<vector<short>> forest;

	while (true)
	{
		getline(cin, input);
		if (input.empty())
		{
			break;
		}

		addForestLine(input, forest);
	}
	
	/*TASK 1*/
	size_t borderTrees = (forest.size() * 2) + ((forest[0].size() - 2) * 2);
	visibleTrees = countVisibleTrees(forest) + borderTrees;

	/*TASK 2*/
	bestTreeVision = getBestTreeVision(forest);

	cout << "Total visible trees: " << visibleTrees << endl; //TASK 1
	cout << "Best tree vision is: " << bestTreeVision << endl; //TASK 2

	return 0;
}

void addForestLine(string& input, vector<vector<short>>& forest)
{
	size_t forestRows = forest.size();
	size_t forestSize = input.size();
	vector<short> forestRow;
	for (size_t i = 0; i < forestSize; i++)
	{
		short tree = (short)input[i] - 48;
		forestRow.push_back(tree);
	}
	forest.push_back(forestRow);
}

size_t countVisibleTrees(vector<vector<short>>& forest)
{
	size_t counter = 0, forestRows = forest.size(), forestColls = forest[0].size();
	
	for (size_t i = 1; i < forestRows - 1; i++)
	{
		for (size_t j = 1; j < forestColls - 1; j++)
		{
			bool isInvisibleAbove = false, isInvisibleUnder = false, isInvisibleOnLeft = false, isInvisibleOnRight = false;

			//up
			for (int k = i - 1; k >= 0 ; k--)
			{
				if (forest[k][j] >= forest[i][j])
				{
					isInvisibleAbove = true;
					break;
				}
			}
			if (!isInvisibleAbove)
			{
				counter++;
				continue;
			}
			//down
			for (size_t k = i + 1; k <= forestRows - 1; k++)
			{
				if (forest[k][j] >= forest[i][j])
				{
					isInvisibleUnder = true;
					break;
				}
			}
			if (!isInvisibleUnder)
			{
				counter++;
				continue;
			}
			//left
			for (int k = j - 1; k >= 0; k--)
			{
				if (forest[i][k] >= forest[i][j])
				{
					isInvisibleOnLeft = true;
					break;
				}
			}
			if (!isInvisibleOnLeft)
			{
				counter++;
				continue;
			}
			//right
			for (size_t k = j + 1; k <= forestColls - 1; k++)
			{
				if (forest[i][k] >= forest[i][j])
				{
					isInvisibleOnRight = true;
					break;
				}
			}
			if (!isInvisibleOnRight)
			{
				counter++;
				continue;
			}
		}
	}

	return counter;
}

size_t getBestTreeVision(vector<vector<short>>& forest)
{
	size_t bestVision = 0, forestRows = forest.size(), forestColls = forest[0].size();

	for (size_t i = 1; i < forestRows - 1; i++)
	{
		for (size_t j = 1; j < forestColls - 1; j++)
		{
			size_t score = 1;

			//up
			for (int k = i - 1, treeVision = 1; k >= 0; k--, treeVision++)
			{
				if ((forest[k][j] >= forest[i][j]) || k == 0)
				{
					score *= treeVision;
					break;
				}
			}
			//down
			for (size_t k = i + 1, treeVision = 1; k <= forestRows - 1; k++, treeVision++)
			{
				if ((forest[k][j] >= forest[i][j]) || k == forestRows - 1)
				{
					score *= treeVision;
					break;
				}
			}
			//left
			for (int k = j - 1, treeVision = 1; k >= 0; k--, treeVision++)
			{
				if ((forest[i][k] >= forest[i][j]) || k == 0)
				{
					score *= treeVision;
					break;
				}
			}
			//right
			for (size_t k = j + 1, treeVision = 1; k <= forestColls - 1; k++, treeVision++)
			{
				if ((forest[i][k] >= forest[i][j]) || k == forestColls - 1)
				{
					score *= treeVision;
					break;
				}
			}
			
			bestVision = (score > bestVision) ? score : bestVision;
		}
	}

	return bestVision;
}
