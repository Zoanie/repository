//============================================================================
// Name        : bit-flipping.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : http://leetcode.com
//============================================================================

#ifdef TIME_SENSITIVE_COMPILE
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#else
#include <bits/stdc++.h>
#endif
using namespace std;

/*
 * Binary Gap
 * Find longest sequence of zeros in binary representation of an integer N.
 * N is an integer within the range [1..2,147,483,647].
 */
int binaryGap(unsigned num)
{
	unsigned bitnum = 0;
	unsigned zeros = 0;
	unsigned ones = 0;
	unsigned lastbit = 0;
	unsigned bitmask = 0x01;
	unsigned max_zeros_seq = 0;
	bool counting_zeros = false;
	//int max_ones_seq = 0;

	while((bitnum < 32)) {
		bitnum++;
		if(bitmask & num) {
			if(counting_zeros) {
				max_zeros_seq = max(zeros, max_zeros_seq);
			}
			counting_zeros = true;
			zeros = 0;
			if(lastbit)
				ones++;
			lastbit = 1;
		}
		else {
			ones = 0;
			if(counting_zeros) {
				if(!lastbit)
					zeros++;
			}
			lastbit = 0;
		}
		bitmask <<= 1;
	}
	return max_zeros_seq;
}

// Write a function that takes an unsigned integer and returns the number of '1' bits it has (also known as the Hamming weight).
/*
or example let N is equal to 12 that is 1100 in binary.

The first check while( N ) says that at least one bit is set in the number.
Then 1 is subtracted from N. N will be equal to

1011

Because in the original N all bits after the second bit were equal to 0 then
N & N -1 will store only bits equal to 1 before the second bit that is the result will be

n=1100
n-1=10FF
sum = 0
// first while loop
while(n != 0) {
  sum++ (=1)
  n = n & (n-1):
  n = 1100 & 1011
  n = 1000
/////
n = 1000
n -1 = 0FFF
while(n != 0) {
  sum++ (=2)
  n = n & (n-1):
  n = 1000 & 0FFF
  n = 0
/////
n = 0
sum = 2

 */
int hammingWeight(int n) {
    int sum = 0;
    while (n != 0) {
        sum++;
        n &= (n - 1);
    }
    return sum;
}

int hammingDistance(int x, int y) {
    // bitwise exclusive OR provides a 1 in the position of bits
    // that are different
    // example: x=10, y=1
    // x ^ y = b1010 ^ 0001 = 1011 (3 bits are different)
    //
    int z = x ^ y;
    int setBits = 0;

    while (z > 0) {
        setBits += z & 1;
        z >>= 1;
    }

    return setBits;
}

//Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.
int rangeBitwiseAnd(int m, int n) {
    while (m < n) {
      // turn off rightmost 1-bit
      n = n & (n - 1);
    }
    return m & n;
}

uint32_t reverseBits(uint32_t n) {
    uint32_t ret = 0, power = 31;
    while (n != 0) {
      ret += (n & 1) << power;
      n = n >> 1;
      power -= 1;
    }
    return ret;
}

uint32_t reverseBitsV2(uint32_t n) {
    n = (n >> 16) | (n << 16);
    n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
    n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
    n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
    n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    return n;
}

#define INT_BITS 32

/*Function to left rotate n by d bits*/
int rotateBitsLeft(int n, unsigned int d)
{
	/* In n<<d, last d bits are 0. To
     put first 3 bits of n at
    last, do bitwise or of n<<d
    with n >>(INT_BITS - d) */
	return (n << d)|(n >> (INT_BITS - d));
}

/*Function to right rotate n by d bits*/
int rotateBitsRight(int n, unsigned int d)
{
    /* In n>>d, first d bits are 0.
    To put last 3 bits of at
    first, do bitwise or of n>>d
    with n <<(INT_BITS - d) */
    return (n >> d)|(n << (INT_BITS - d));
}

/*
 * Given a non negative integer number num.
 * For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their
 * binary representation and return them as an array.
 */
int* countBits(int num) {
      int* ans = new int[num + 1];
      for (int i = 1; i <= num; ++i)
        ans[i] = ans[i >> 1] + (i & 1); // x / 2 is x >> 1 and x % 2 is x & 1
      return ans;
}

bool hasAlternatingBits(int n) {
	bool consecutive_ones = (n & (n >> 1)) == 0;			// 0x01101: co = 0x01101 & 0x00110 = 0x00100 != 0;
	bool consecutive_zeros = (n & (n >> 2)) == (n >> 2);	// 0x10010: co = 0x10010 & 0x00100 = 0x00000 != 0x00100
	return consecutive_ones && consecutive_zeros;
}

bool hasConsecutiveOnes(unsigned n) {
	bool consecutive_ones = (n & (n >> 1)) == 0;		// 0x01101: co = 0x01101 & 0x00110 = 0x00100 != 0;
	return consecutive_ones;
}

bool hasConsecutiveZeros(unsigned n) {
	bool consecutive_zeros = (n & (n >> 2)) == (n >> 2);	// 0x10010: co = 0x10010 & 0x00100 = 0x00000 != 0x00100
	return consecutive_zeros;
}

int setBitNumber(int n)
{
    // Below steps set bits after
    // MSB (including MSB)

    // Suppose n is 273 (binary
    // is 100010001). It does following
    // 100010001 | 010001000 = 110011001
    n |= n>>1;

    // This makes sure 4 bits
    // (From MSB and including MSB)
    // are set. It does following
    // 110011001 | 001100110 = 111111111
    n |= n>>2;

    n |= n>>4;
    n |= n>>8;
    n |= n>>16;

    // Increment n by 1 so that
    // there is only one set bit
    // which is just before original
    // MSB. n now becomes 1000000000
    n = n + 1;

    // Return original MSB after shifting.
    // n now becomes 100000000
    return (n >> 1);
}
/*
 * Given an integer array arr. You have to sort the integers in the array in
 * ascending order by the number of 1's in their binary representation and in
 * case of two or more integers have the same number of 1's you have to sort
 * them in ascending order.
 *
 * Return the sorted array.
 * Input: arr = [0,1,2,3,4,5,6,7,8]
Output: [0,1,2,4,8,3,5,6,7]
Explanation: [0] is the only integer with 0 bits.
[1,2,4,8] all have 1 bit.
[3,5,6] have 2 bits.
[7] has 3 bits.
The sorted array by bits is [0,1,2,4,8,3,5,6,7]
 */
class SortIntegersSolution {
public:
    static int countBits (int& num){
        int x = 1, count = 0;
        while (x <= num){
            if (num & x){
                count ++;
            }
            x = x << 1;
        }
        return count;
    }
    static bool compare (int& n1, int& n2){
        int bit1 = countBits(n1);
        int bit2 = countBits(n2);
        if (bit1 == bit2){
            return n1 < n2;
        }
        return bit1 < bit2;
    }

    vector<int> sortByBits(vector<int>& arr) {
        sort(arr.begin(), arr.end(), compare);
        return arr;
    }
};

/*
 * We have an array A of non-negative integers.

For every (contiguous) subarray B = [A[i], A[i+1], ..., A[j]] (with i <= j), we take the
bitwise OR of all the elements in B, obtaining a result A[i] | A[i+1] | ... | A[j].

Return the number of possible results.
(Results that occur more than once are only counted once in the final answer.)
 */
int subarrayBitwiseORs(vector<int>& A) {
	set<int> s(A.begin(),A.end());
	int vec_size = A.size();
	for(int i=0; i<vec_size; i++){
		int j = i - 1;
		int x = 0, y = A[i];
		s.insert(y);
		while(j >= 0 && x != y){
			x |= A[j];
			y |= A[j];
			s.insert(y);
			j--;
		}
	}
	return s.size();
}

// C++ program to compute exponential
// value under modulo using binary
// exponentiation.

#define LARGE_PRIME_MODULO 1000000007 // prime modulo value

long int exponentiation(long int base,
						long int exp)
{
	if (exp == 0)
		return 1;

	if (exp == 1)
		return base % LARGE_PRIME_MODULO;

	long int t = exponentiation(base, exp / 2);
	t = (t * t) % LARGE_PRIME_MODULO;

	// if exponent is even value
	if (exp % 2 == 0)
		return t;

	// if exponent is odd value
	else
		return ((base % LARGE_PRIME_MODULO) * t) % LARGE_PRIME_MODULO;
}

// Driver Code
int test_fast_exponentation()
{
	long int base = 5;
	long int exp = 100000;

	long int modulo = exponentiation(base, exp);
	cout << modulo << endl;
	return 0;
}

// This Code is contributed by mits

int main() {
	cout << "http://leetcode.com" << endl; 

	unsigned N[10] = {1041, 1, 0x101, 0x1001, 0x1000100, 0x10000100, 0x10000001, 0x10000000, 0x10001, 0x100001};
	for(int test=0; test < 10; test++) {

		cout << "binary gap for N=" << N[test] << binaryGap(N[test]) << endl;
	}
	return 0;
}
