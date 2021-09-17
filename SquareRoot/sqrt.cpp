/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Gavin Pan
 * Version : 1.0
 * Date    : September 2, 2020
 * Description : Computes the square root using Newton's method
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

double sqrt(double num, double epsilon)
{
	double last_guess = num, next_guess = (last_guess + num/last_guess)/2;

	if(num < 0)
		return numeric_limits<double>::quiet_NaN();

	if(abs(num - 0) < epsilon or abs(num - 1) < epsilon)
		return num;

	while(abs(last_guess - next_guess) > epsilon)
	{
		last_guess = next_guess;
		next_guess = (last_guess + num/last_guess)/2;
	}

	return next_guess;
}

int main(int argc, char* const argv[])
{
	double epsilon;
	char* end = nullptr;

	if(argc < 2 or argc >3)
	{
		cout << "Usage: ./sqrt <value> [epsilon]" << endl;
		return 0;
	}
	double num = strtod(argv[1], &end);

	if(argv[1] == end)
	{
		cout << "Error: Value argument must be a double." << endl;
		return 0;
	}

	if(argc < 3)
		epsilon = 1e-7;
	else
		epsilon = strtod(argv[2], &end);

	if(epsilon <= 0 or end == argv[2])
	{
		cout << "Error: Epsilon argument must be a positive double." << endl;
		return 0;
	}

	cout << fixed << setprecision(8) << sqrt(num, epsilon) << endl;

	return 0;
}
