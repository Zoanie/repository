//============================================================================
// Name        : dynamic-fibonacci.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://repl.it/@aneagoie/Fib-Dynamic-Programming#main.js
//============================================================================

#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int, int> fib_cache;

int calculations = 0;
int fibonacci(int n)
{ //O(2^n)

  if (n < 2) {
    return n;
  }
  return fibonacci(n-1) + fibonacci(n-2);
}

//O(n)
int fibonacciDynamic(int n)
{
	int result;

	if(n < 10) {
		int first10[10]= {0,1,1,2,3,5,8,13,21,34};
		return first10[n];
	}
	else {
		auto cached = fib_cache.find(n);
		if(cached != end(fib_cache)) {
			return cached->second;
		}
		else {
			result = fibonacciDynamic(n-1) + fibonacciDynamic(n-2);
			fib_cache.emplace(n, result);
		}
	}
	return result;

}


/*
console.log('Slow', fibonacci(35))
console.log('DP', fasterFib(100));
console.log('DP2', fibonacciMaster2(100));
console.log('we did ' + calculations + ' calculations');
*/


int main() {
	cout << "https://repl.it/@aneagoie/Fib-Dynamic-Programming#main.js\n" << endl; // prints https://repl.it/@aneagoie/Fib-Dynamic-Programming#main.js

	for(int n=0; n<=40; n++) {
		printf("Fibonacci(%d) = %d\n", n, fibonacciDynamic(n));
	}
	return 0;
}
