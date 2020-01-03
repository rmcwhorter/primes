#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <algorithm> 
#include <chrono> 
using namespace std;
using namespace std::chrono; 

bool is_prime(long long int n)  
{  
    // Corner cases  
    if (n <= 1)  return false;  
    if (n <= 3)  return true;  
    
    // This is checked so that we can skip   
    // middle five numbers in below loop  
    if (n%2 == 0 || n%3 == 0) return false;  
    
    for (int i=5; i*i<=n; i=i+6)  
        if (n%i == 0 || n%(i+2) == 0)  
           return false;  
    
    return true;  
}  
  
// Function to return the smallest 
// prime number greater than N 
int next_prime(long long int N) 
{ 
  
    // Base case 
    if (N <= 1) 
        return 2; 
  
    long long int prime = N; 
    bool found = false; 
  
    // Loop continuously until isPrime returns 
    // true for a number greater than n 
    while (!found) { 
        prime++; 
  
        if (is_prime(prime)) 
            found = true; 
    } 
  
    return prime; 
} 

void print(std::vector<long long int> const &input)
{
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ';
	}
}

vector<long long int> factorize(long long int n) {
    long long int live = n;
    vector<long long int> rtn;

    long long int prime = 2;
    while (accumulate(begin(rtn), end(rtn), 1, std::multiplies<double>()) != n) {
        if (live % prime == 0) {
            rtn.push_back(prime);
            live = live / prime;
        } else {
            prime = next_prime(prime);
        }
    }

    return rtn;
}

int main()
{
    cout << "=====SOF=====\n\n";
    int int_1 = 858645989;
    int int_2 = 977666464;
    
    vector<int> times_1;
    vector<int> times_2;
    int n = 100;

    for (int i = 0; i < n; i++) {
        auto start = high_resolution_clock::now(); 
        factorize(int_1);
        auto stop = high_resolution_clock::now(); 
        times_1.push_back(duration_cast<microseconds>(stop - start).count());
    }
    for (int i = 0; i < n; i++) {
        auto start = high_resolution_clock::now(); 
        factorize(int_2);
        auto stop = high_resolution_clock::now(); 
        times_2.push_back(duration_cast<microseconds>(stop - start).count());
    }

    float average_1 = accumulate( times_1.begin(), times_1.end(), 0.0)/times_1.size();
    float average_2 = accumulate( times_2.begin(), times_2.end(), 0.0)/times_2.size();

    cout << int_1 << " has prime factorization \n";
    print(factorize(int_1));
    cout << "\n" << int_2 << " has prime factorization \n";
    print(factorize(int_2));
    cout << "\n";

    cout << "\nFactoring " << int_1 << " took an average of " << average_1 << " microseconds, over " << n << " trials.\n";
    cout << "Factoring " << int_2 << " took an average of " << average_2 << " microseconds, over " << n << " trials.\n";


    cout << "\n\n=====EOF=====\n";

}