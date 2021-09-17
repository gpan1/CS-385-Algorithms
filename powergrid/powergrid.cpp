/*******************************************************************************
 * Name          : powergrid.cpp
 * Author        : Gavin Pan
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : 12/14/2020
 * Description   : Final Project
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <limits.h>
#include <iomanip>
#include <queue>
using namespace std;

class edge
{
	public:
		int x,y,z;
		string address;
		edge(int x1, int y1, int z1, string s)
		{
			x = x1;
			y = y1,
			z = z1;
			address = s;
		}
		bool operator > (const edge& a, const edge& b)
		{
			return a.z > b.z;
		}
		bool operator < (const edge& a, const edge& b)
		{
			return a.z < b.z;
		}
		bool operator = (const edge& a, const edge& b)
		{
			return a.z = b.z;
		}
};

//global variables
int m;
vector <vector<edge>> list;
vector<edge> primsmells;

bool plsdontfailmedrb(edge x, edge y)
{
	if(x.address.compare(y.address) >= 0)
		return false;
	return true;
}
void mst()
{
	/*vector<edge> small;
	for(unsigned int i = 0; i < list.size(); i++)
	{
		int index = -1;
	    int min = INT_MAX;
	    for(unsigned int k = 0; k < list[i].size(); k++)
	    {
	       if(list[i][k].z  < min)
	       {
	    	   min = list[i][k].z;
	    	   index = k;
	       }
	    }
	    if(index == -1)
	    {
	    	cerr << "No solution.";
	    	exit(0);
	    }
	    small.push_back(list[i][index]);
	}
	string s = "" + primsmells[0].address;
	s+= ",";
	for(unsigned int i = 0; i < small.size(); i++)
	{
		string add =  small[i].address;
		if(s.find(add) == string::npos)
		{
			s += small[i].address;
			s+= ",";
			primsmells.push_back(small[i]);
		}
	}*/

}
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <input file>" << endl;
		return 1;
	}
	ifstream input_file(argv[1]);
	if (!input_file)
	{
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	input_file.exceptions(ifstream::badbit);
	try {
		string line;
		stringstream ss;
		getline(input_file, line);
		ss << line;
		if (!(ss >> m) || m < 1 || m > 1000) {
			cerr << "Error: Invalid number of vertices '" << line <<
					"' on line 1." << endl;
			return 1;
		}
		ss.clear();
		if(m == 1)
		{
			cout << "No solution.";
			return 1;
		}
		vector<string> inputs;
		vector<edge> p;
		while(getline(input_file, line))
		{
			inputs.push_back(line);
		}
		for(int i = 0; i < m; i++)
		{
			list.push_back(p);
		}
		for(long unsigned int i = 0; i < inputs.size(); i++)
		{
			size_t n = count(inputs[i].begin(), inputs[i].end(), ',');
			if(n != 3)
			{
				cerr << "Error: Invalid edge data '" + inputs[i] + "' on line " + to_string(i+2) + ".";
				return 1;
			}
			int x,y,z;
			for(int k = 0; k < 3; k++)
			{
				size_t f = inputs[i].find(',');
				int size = inputs[i].size();
				if(k == 0)
				{
					try {
					   x = stoi(inputs[i].substr(0,f));
					   if(x > m || x < 1)
					   {
						   throw invalid_argument("x");
					   }
					} catch(const invalid_argument &) {
					   // invalid starting vertex, then exit
						cerr << "Error: Starting vertex '" << inputs[i].substr(0,f) << "' on line " << i+2 << " is not among valid values 1-" << m << ".";
						return 1;
					}
					 inputs[i] = inputs[i].substr(f+1,size);
				}
				else if(k == 1)
				{
					try {
						y = stoi(inputs[i].substr(0,f));
						if(y < 1 || y > m)
						{
							throw invalid_argument("y");
						}
					} catch(const invalid_argument &) {
						// invalid starting vertex, then exit
						cerr << "Error: Ending vertex '" << inputs[i].substr(0,f) << "' on line " << i+2 << " is not among valid values 1-" << m << ".";
						return 1;
					}
					inputs[i] = inputs[i].substr(f+1,size);
				}
				else
				{
					try {
						z = stoi(inputs[i].substr(0,f));
						if(z < 1)
						{
							throw invalid_argument("z");
						}
					} catch(const invalid_argument &) {
						// invalid starting vertex, then exit
						cerr << "Error: Invalid edge weight '" << inputs[i].substr(0,f) << "' on line " << i+2 << ".";
						return 1;
					}
					inputs[i] = inputs[i].substr(f+1,size);
				}
			}
			if(i == 0)
				primsmells.push_back(edge(x,y,z, inputs[i]));
			list[x-1].push_back(edge(x,y,z, inputs[i]));
			list[y-1].push_back(edge(x,y,z, inputs[i]));
		}
		if(inputs.size() == 0)
		{
			cout << "No solution.";
			return 1;
		}
		input_file.close();
		mst();
		sort(primsmells.begin(), primsmells.end(), plsdontfailmedrb);
		int meters = 0;
		for(unsigned int i = 0; i < primsmells.size(); i++)
		{
			meters += primsmells[i].z;
		}
		cout << "Total wire length (meters): " << meters << endl;
		for(unsigned int i = 0; i < primsmells.size(); i++)
		{
			cout<< primsmells[i].address << " [" << primsmells[i].z << "]" << endl;
		}
	} catch (const ifstream::failure &f)
	{
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}

}


