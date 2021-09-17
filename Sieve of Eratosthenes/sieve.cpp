/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Gavin Pan
 * Date        : September 15, 2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.

	const int max_prime_width = num_digits(max_prime_),primes_per_row = 80/(max_prime_width + 1);

	int count = 0;

	cout << endl << "Number of primes found: " << num_primes_ << endl;

	cout << "Primes up to " << limit_ << ":" << endl;

	for(int i =2; i <= limit_; i++)
	{
		if(is_prime_[i])
		{
			if(count == primes_per_row) //resets counter
			{
				count = 0;
				cout << endl;
			}
			if(primes_per_row < num_primes_) // checks if number of primes is less than primes_per_row
			{
				cout << setw(max_prime_width)<< i;
			}
			else
				cout << i;
			count++;
			if(max_prime_!= i && count !=primes_per_row) // adds space if prime isnt at end of the line
				cout << " ";
		}
	}

}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found

	int primes = 0;
	for(int i = 2; i <= limit_; i++)
	{
		if(is_prime_[i])
		{
			primes++;
		}
	}
    return primes; // finds amount of primes
}

void PrimesSieve::sieve() {
	// TODO: write sieve algorithm

	for(int i = 2; i <= limit_; i++)
	{
		is_prime_[i] = true;
	}//makes it all true

	for(int i = 2; i <= sqrt (limit_); i++)
	{
		if(is_prime_[i])
		{
			for(int j = i*i; j <= limit_; j= j+i)
			{
				is_prime_[j] = false;
			}
		}
	}//changes the numbers that aren't prime to false

	for(int i = limit_; i > 0; i--)
		{
			if(is_prime_[i])
			{
				max_prime_ = i;		// updates max_prime
				break;
			}
		}

	num_primes_ = count_num_primes(); //updates num_prime_

}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
	int digits = 0;

	while(num!=0)
	{
		num = num/10;
		digits++;
	}

    return digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.

    PrimesSieve x = PrimesSieve(limit);

    x.display_primes();

    return 0;
}
