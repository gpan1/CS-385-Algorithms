/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Gavin Pan and David Son
 * Version     : 1.0
 * Date        : 10/29/2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
	long inversions = 0;
	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			if (array[i] > array[j]) {
				inversions++;
			}
		}
	}
	return inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
	int *scratch = new int[length];
	long out = mergesort(array, scratch, 0, length - 1);
	delete[] scratch;
	return out;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	int mid, L, H;
	long inversions = 0;
	if (low < high) {
		mid = low + (high - low) / 2;
		inversions += mergesort(array, scratch, low, mid);
		inversions += mergesort(array, scratch, mid+1, high);

		L = low;
		H = mid + 1;
		for (int i = low; i <= high; i++) {
			// If L passes the midpoint, we can just merge the rest of the right side.
			// If H passes high, we can just merge the rest of the left side;
			if (L <= mid && (H > high || array[L] <= array[H])) {
				scratch[i] = array[L++];
			} else {
				scratch[i] = array[H++];
				inversions += (mid - L + 1);
				// Increment inversions here
			}
		}

		for (int i = low; i <= high; i++) {
			array[i] = scratch[i];
		}
	}
	return inversions;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
	if (argc > 2) {
		cerr << "Usage: ./inversioncounter [slow]" << endl;
		return 1;
	}

	bool slow = false;
	if (argc == 2) {
		string arg = argv[1];
		if (arg.compare("slow") != 0) {
			cerr << "Error: Unrecognized option '" << arg << "'." << endl;
			return 1;
		}
		slow = true;
	}
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if(values.size() < 1)
    {
      cerr << "Error: Sequence of integers not received.";
      return 1;
    }

    // TODO: produce output
	cout << "Number of inversions: ";
	if (slow) {
		cout << count_inversions_slow(&values[0], values.size());
	} else {
		cout << count_inversions_fast(&values[0], values.size());
	}
	cout << endl;

    return 0;
}
