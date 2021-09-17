/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : David Son and Gavin Pan
 * Version     : 1.0
 * Date        : December 7 2020
 * Description : Implementation of Floyd's shortest
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
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

using namespace std;

// Global variables
vector<vector<vector<long>>> int_vertices;

// Helper Functions

// Returns string length of a (positive) long
long len(const long max_val) {
	return to_string(max_val).length();
}

// Main functions

// Uses Floyd's algorithm to find the shortest path
vector<vector<long>> floyd(const vector<vector<long>> matrix) {

	int n = matrix.size();
	vector<vector<vector<long>>> d(n+1, vector<vector<long>>(n, vector<long>(n, LONG_MAX)));
	vector<vector<long>> m(n, vector<long>(n, LONG_MAX));
	d[0] = matrix;

	for (int k = 1; k <= n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (d[k-1][i][k-1] == LONG_MAX || d[k-1][k-1][j] == LONG_MAX) {
					d[k][i][j] = d[k-1][i][j];
				} else {
					if (d[k-1][i][k-1] + d[k-1][k-1][j] < d[k-1][i][j]) {
						m[i][j] = k-1;
					}
					d[k][i][j] = min(d[k-1][i][j], d[k-1][i][k-1] + d[k-1][k-1][j]);
				}
			}
		}
	}

	int_vertices.push_back(m);
	return d[n];
}

// Prints the given matrix
void display_table(const vector<vector<long>> matrix, const string label = "", const bool use_letters = false) {
	int num_vertices = matrix.size();

	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < LONG_MAX && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}

	int max_cell_width = use_letters ? len(max_val) :
			len(max(static_cast<long>(num_vertices), max_val));
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}

	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == LONG_MAX) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

string path_helper(const vector<vector<long>> floyd_mat, const int i, const int j) {


	if (int_vertices[0][i][j] == LONG_MAX) {
		string s = "";
		s += char(i + 'A');
		if (i == j) {
			return s;
		}
		s += char(j + 'A');
		return s;
	}

	string s1 = path_helper(floyd_mat, i, int_vertices[0][i][j]);
	string s2 = path_helper(floyd_mat, int_vertices[0][i][j], j);

	return s1 + s2.substr(1);
}

int main(int argc, char *argv[]) {
	// Error checking
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}

	// Create an ifstream object.
	ifstream input_file(argv[1]);
	// If it does not exist, print an error message.
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}

	// Add read errors to the list of exceptions the ifstream will handle.
	input_file.exceptions(ifstream::badbit);

	try {
		string line;
		int m;
		stringstream ss;

		// Use getline to read in a line.
		// See http://www.cplusplus.com/reference/string/string/getline/
		getline(input_file, line);
		ss << line;
		if (!(ss >> m) || m < 1 || m > 26) {
			cerr << "Error: Invalid number of vertices '" << line <<
					"' on line 1." << endl;
			return 1;
		}
		ss.clear();

		// Instantiate m x m matrix with default value LONG_MAX
		// For matrix[i][j], i is starting vertex, j is ending vertex
		vector<vector<long>> matrix(m, vector<long>(m, LONG_MAX));
		unsigned int line_number = 2;

		// A vertex is 0 distance from itself
		for (int i = 0; i < m; i++) {
			matrix[i][i] = 0;
		}

		// Get every line and put it in matrix
		while (getline(input_file, line)) {
			string arr[3];
			string val = "";
			int i = 0;

			// Split into three parts if possible
			for (char c : line) {
				if (i < 3) {
					if (c != ' ') {
						val += c;
					} else {
						arr[i++] = val;
						val = "";
					}
				}
			}
			arr[i++] = val;

			// Not enough arguments
			if (i < 3) {
				cerr << "Error: Invalid edge data '" << line <<
						"' on line " << line_number << "." << endl;
				return 1;
			}

			// Check if 1st and 2nd input are within range
			for (int i = 0; i < 2; i++) {

				if (arr[i].length() != 1) {
					if (i == 0) {
						cerr << "Error: Starting ";
					} else {
						cerr << "Error: Ending ";
					}
					cerr << "vertex '" << arr[i] << "' on line " << line_number <<
							" is not among valid values A-" << char('A' + m - 1) << "." << endl;
					return 1;
				}

				// arr[i] is of length 1
				char c = arr[i][0];
				if (c < 'A' || c > ('A' + m - 1)) {
					if (i == 0) {
						cerr << "Error: Starting ";
					} else {
						cerr << "Error: Ending ";
					}
					cerr << "vertex '" << arr[i] << "' on line " << line_number <<
							" is not among valid values A-" << char('A' + m - 1) << "." << endl;
					return 1;
				}
			}

			// Check if edge weight is valid
			int n;
			ss << arr[2];
			if (!(ss >> n) || (n < 1)) {
				cerr << "Error: Invalid edge weight '" << arr[2] <<
						"' on line " << line_number << "." << endl;
				return 1;
			}
			ss.clear();

			// Add to vector
			int c1 = arr[0][0] - 'A', c2 = arr[1][0] - 'A';
			matrix[c1][c2] = n;
			++line_number;
		}
		// Don't forget to close the file.
		input_file.close();

		// Algorithm

		// Have # of vertices (m) and graph (graph), which is a vector of vector of ints
		display_table(matrix, "Distance matrix:");

		// Use Floyd's method
		vector<vector<long>> floyd_mat = floyd(matrix);
		display_table(floyd_mat, "Path lengths:");
		display_table(int_vertices[0], "Intermediate vertices:", true);

		// Print shortest paths
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				cout << char(i + 'A') << " -> " << char(j + 'A') <<
						", distance: ";

				if (floyd_mat[i][j] == LONG_MAX) {
					cout << "infinity, path: none\n";
				} else {
					cout << floyd_mat[i][j] << ", path: ";
					string s = path_helper(floyd_mat, i, j);
					cout << s[0];
					for (size_t i = 1; i < s.length(); i++) {
						cout << " -> " << s[i];
					}
					cout << "\n";
				}
			}
		}

	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}

	return 0;
}
