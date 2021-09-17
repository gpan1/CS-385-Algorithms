/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : David Son and Gavin Pan
 * Date        : October 19th 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <queue>

using namespace std;

struct State {
	int a, b, c;
	string directions;
	vector<State> parent;
	State(int _a, int _b, int _c, string _directions) :
    	a{_a}, b{_b}, c{_c}, directions{_directions} { }
	// String representation of state in tuple form.
	string to_string() {
    	ostringstream oss;
    	oss << "(" << a << ", " << b << ", " << c << ")";
    	return oss.str();
	}
};

void print_result(State current)
{
	if (current.parent.size() != 0) {
		print_result(current.parent[0]);
		cout << endl;
	}
	if (current.directions.at(5) == '1' && current.directions.at(6) == ' ') {
		current.directions.erase(current.directions.begin() + 13);
	}
	cout << current.directions << " " << current.to_string();
}

void bfs(int a, int b, int c, int gs[])
{
	vector<string> visited;
	queue<State> q;
	State goal_state(gs[0], gs[1], gs[2], "");

	q.push(State(0, 0, c, "Initial state."));
	while (q.size() > 0)
	{
		State current = q.front();
		q.pop();

		if(goal_state.to_string().compare(current.to_string()) == 0)
		{
			while (q.size() > 0) {
				q.pop();
			}
			print_result(current);
			return;
		}

    	if(find(visited.begin(), visited.end(), current.to_string()) != visited.end())
		{
			continue;
		}

		visited.push_back(current.to_string());

		// Please help
		if (current.a < a) {
			if (current.c > 0) {
				if (current.c + current.a > a) {
					State s(a, current.b, current.c - (a - current.a), "Pour " + to_string(a - current.a) + " gallons from C to A.");
					s.parent.push_back(current);
					q.push(s);
				} else {
					State s(current.a + current.c, current.b, 0, "Pour " + to_string(current.c) + " gallons from C to A.");
					s.parent.push_back(current);
					q.push(s);
				}
			}
			if (current.b > 0) {
				if (current.b + current.a > a) {
					State s(a, current.b - (a - current.a), current.c, "Pour " + to_string(a - current.a) + " gallons from B to A.");
					s.parent.push_back(current);
					q.push(s);
				} else {
					State s(current.a + current.b, 0, current.c, "Pour " + to_string(current.b) + " gallons from B to A.");
					s.parent.push_back(current);
					q.push(s);
				}
			}
		}
		if (current.b < b) {
			if (current.c > 0) {
				if (current.c + current.b > b) {
					State s(current.a, b, current.c - (b - current.b), "Pour " + to_string(b - current.b) + " gallons from C to B.");
					s.parent.push_back(current);
					q.push(s);
				} else {
					State s(current.a, current.b + current.c, 0, "Pour " + to_string(current.c) + " gallons from C to B.");
					s.parent.push_back(current);
					q.push(s);
				}
			}
			if (current.a > 0) {
				if (current.a + current.b > b) {
					State s(a - (b - current.b), b, current.c, "Pour " + to_string(b - current.b) + " gallons from A to B.");
					s.parent.push_back(current);
					q.push(s);
				} else {
					State s(0, current.b + current.a, current.c, "Pour " + to_string(current.a) + " gallons from A to B.");
					s.parent.push_back(current);
					q.push(s);
				}
			}
		}
		if (current.c < c) {
			if (current.b > 0) {
				if (current.b + current.c > c) {
					State s(current.a, b - (c - current.c), c, "Pour " + to_string(c - current.c) + " gallons from B to C.");
					s.parent.push_back(current);
					q.push(s);
				} else {
					State s(current.a, 0, current.c + current.b, "Pour " + to_string(current.b) + " gallons from B to C.");
					s.parent.push_back(current);
					q.push(s);
				}
			}
			if (current.a > 0) {
				if (current.a + current.c > c) {
					State s(a - (c - current.c), current.b, c, "Pour " + to_string(c - current.c) + " gallons from A to C.");
					s.parent.push_back(current);
					q.push(s);
				} else {
					State s(0, current.b, current.c + current.a, "Pour " + to_string(current.a) + " gallons from A to C.");
					s.parent.push_back(current);
					q.push(s);
				}
			}
		}

	}
	cout << "No solution.";
	return;
}

int main(int argc, char * const argv[])
{
	if (argc != 7)
	{
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
		return 1;
	}

	// Indices 0, 1, 2 refer to jug A, B, and C's capacities
	// Indices 3, 4, 5 refer to jug A, B, and C's goal states
	int nums[6];
	istringstream iss;

	for (int i = 1; i < 7; i++)
	{
		iss.str(argv[i]);
		if (!(iss >> nums[i-1]) || nums[i-1] < 0 || (i <= 3 && nums[i-1] == 0))
		{
			string type;
			string jug;

			if (i <= 3)
			{
				type = "capacity";
			}
			else
			{
				type = "goal";
			}

			if (i == 1 || i == 4)
			{
				jug = "A";
			}
			else if (i == 2 || i == 5)
			{
				jug = "B";
			}
			else
			{
				jug = "C";
			}

			cerr << "Error: Invalid " << type << " \'" << argv[i] << "\' for jug " << jug << ".";
			return 1;
        }
		iss.clear();
    }

	int sumGoal = 0;

	for (int i = 0; i < 3; i++)
	{
		sumGoal += nums[i + 3];
		if(nums[i+3] > nums[i])
	    {
			string jug;
			if (i == 0)
			{
				jug = "A";
			}
			else if (i == 1)
			{
				jug = "B";
			}
			else
			{
				jug = "C";
			}
			cerr << "Error: Goal cannot exceed capacity of jug " << jug << ".";
			return 1;
	    }
	}
	if (sumGoal != nums[2])
	{
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
		return 1;
	}

	int goal_state[3];
	for (int i = 3; i < 6; i++) {
		goal_state[i-3] = nums[i];
	}

	bfs(nums[0], nums[1], nums[2], goal_state);
    return 0;
}
