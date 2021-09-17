/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Gavin Pan
 * Date        : 9/24/2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

	for(unsigned int i = 0; i < s.length(); i++)
	{
		if(!islower(s.at(i)))
			return false;
	}

	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	unsigned int vector;
	unsigned int setter;

	char first = s.at(0);

	for(unsigned int i = 0; i < s.length(); i++)
	{
		setter = 1 << (s.at(i) - first);
		if((setter & vector) != 0)
			return false;
		else
			vector = vector | setter;
	}
	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

	if(argc != 2) // checks if it is too long or too short/no input
	{
		cout << "Usage: ./unique <string>";
		return 0;
	}
	if(!is_all_lowercase(argv[1])) //checks if it is all lowercase
	{
		cout << "Error: String must contain only lowercase letters.";
		return 0;
	}
	if(all_unique_letters(argv[1])) // checks if unique
		cout << "All letters are unique.";
	else
		cout << "Duplicate letters found.";

	return 0;




}
