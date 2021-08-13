//============================================================================
// Name        : perfect-squares.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

/*
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
 */

/*
 * Notes:
 *   o The maximum perfect square less than n is sqrt(n).
 *     This means we must look for perfect square numbers between 1 & sqrt(n).
 *   o ps(n) = (j*j) + ps(n - (j*j))
 *
 *     Ex: ps(16) = Sum (#s between 1 and sqrt(16), or 1 and 4) = (4*4) + ps(16 - (16)) = 16 - 0
 *
 *     Ex: ps(12) = Sum (#s between 1 and sqrt(12), or 1 and 3.46, (which rounds to 3, so between 1 and 3)
 *         ps(12) = Sum (3^2 + 1 + 1 + 1) => 4 numbers
 *         ps(12) = Sum (2^2 + 2^2 + 2^2) => 3 numbers   << least number >>
 *         ps(12) = Sum (1 + 1 + 1 +....) => 12 numbers
 *
 *   o Lagrange’s four-square theorem, also known as Bachet’s conjecture, states that every natural number
 *     can be represented as the sum of four integer squares.  This means the maximum result is 4.  We just
 *     need to decide if there exists a solution for 1, 2 or 3 squares.
 *   o Adrien-Marie Legendre completed the theorem in 1797–8 with his three-square theorem, by proving that
 *     a positive integer can be expressed as the sum of three squares if and only if it is not of the form
 *     4^k(8m+7) for integers k and m.
 *   o N. Beguelin noticed in 1774 that every positive integer which is neither of the form 8n + 7, nor of the form 4n, is the sum of three squares
 */
class Solution {
public:
    int numSquares(int n) {

    	if(n <= 3) {
    		return n;
    	}

    	// test for 1
    	int sqrtOfn = sqrt(n);
    	if(sqrtOfn*sqrtOfn == n)
    		return 1;

    	// test for 2
    	int rem = n - sqrtOfn;
    	for(int sum2 = 1; sum2 <= sqrtOfn; sum2++) {
    		rem = n - sum2*sum2;
    		// Perfect square numbers only end in 0, 1, 4, 5, 6, & 9, (not 2, 3, 7 or 8)
    		int lastdigit = rem & 0x0F;
    		if(lastdigit == 2 || lastdigit == 3 || lastdigit == 7 || lastdigit == 8) {
    		    continue;
    		}
    		int sqrtOfrem = sqrt(rem);
    		if(sqrtOfrem*sqrtOfrem == rem)
    		{
    			return 2;
    		}
    	}

        // The result is 4 if n can be written in the
        // form of 4^k*(8*m + 7).
        while ((n & 3) == 0) // n%4 == 0
        {
            n >>= 2;
        }
        if ((n & 7) == 7) // n%8 == 7
        {
            return 4;
        }
        return 3;
    }
};

int main() {
	cout << "https://leetcode.com/problems/perfect-squares/" << endl; // prints https://leetcode.com/problems/perfect-squares/
	Solution NS;

	cout << "Num Squares 12 = " << NS.numSquares(12) << endl;
	cout << "Num Squares 99 = " << NS.numSquares(99) << endl;
	return 0;
}
