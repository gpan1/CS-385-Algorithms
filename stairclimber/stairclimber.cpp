/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Gavin Pan
 * Date        : 10/2/2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs)
{
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

	vector< vector<int> > ways;
	if(num_stairs <= 0)
		ways.push_back(vector<int>());
	else
	{
		for(int i = 1; i < 4; i++)
		{
			if(num_stairs >= i)
			{
				vector< vector<int> > result = get_ways(num_stairs - i);
				for(unsigned int j = 0; j < result.size(); j++)
				{
					result[j].insert(result[j].begin(), i);
				}
				ways.insert(ways.end(), result.begin(), result.end());
			}
		}
	}
	return ways;

}

void display_ways(const vector< vector<int> > &ways)
{
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	unsigned int size = ways.size();
	int count = 0;
	unsigned int size2 = size;

	while(size2!=0)
	{
		size2 = size2/10;
		count++;
	}

	for(unsigned int i =0; i < size; i++)
	{

		cout << setw(count) << i+1 << ". [";
		unsigned int length = ways[i].size();
		for(unsigned int j = 0; j < length; j++)
		{
			if(j == length-1)
				cout << ways[i][j];
			else
				cout << ways[i][j] << ", ";
		}
		cout << "]" << endl;
	}
}

int main(int argc, char * const argv[])
{
	if(argc != 2)
	{
		cerr << "Usage: ./stairclimber <number of stairs>";
		return 1;
	}

	istringstream iss;
	iss.str(argv[1]);
	int numstairs;

	if(!(iss >> numstairs) || numstairs <= 0)
	{
		cerr << "Error: Number of stairs must be a positive integer.";
		return 1;
	}

	vector< vector<int> > x = get_ways(numstairs);
	if(numstairs > 1)
		cout << x.size() << " ways to climb " << numstairs << " stairs." << endl;
	else
		cout << x.size() << " way to climb " << numstairs << " stair." << endl;
	display_ways(x);

	return 0;

}
