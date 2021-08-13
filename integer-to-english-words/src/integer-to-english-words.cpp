//============================================================================
// Name        : integer-to-english-words.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/integer-to-english-words/
//============================================================================

#include <iostream>
#include <boost/lexical_cast.hpp>	// requires installation: sudo apt-get install libboost-all-dev
#include <vector>
#include <queue>
#include <map>

using namespace std;



/*
Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 2^31 - 1.

2^31 -1 = 2,147,483,647

Example 1:

Input: 123
Output: "One Hundred Twenty Three"
Example 2:

Input: 12345
Output: "Twelve Thousand Three Hundred Forty Five"
Example 3:

Input: 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Example 4:

Input: 1,234,567,891
Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"

Extracting a digit from an integer:
Given the number 12345 :

45 is 12345 % 100

5 is 12345 % 10
4 is 12345 / 10 % 10
3 is 12345 / 100 % 10
2 is 12345 / 1000 % 10
1 is 12345 / 10000 % 10
 */
class Solution {
	deque<string> english;
	string result;

public:
	string numberToWords(int num) {
		int digits = num;
		int next_digit = 0;
		int digits_mask = 100;
		int digit_divisor = 1;
		string zero = "Zero";
		string last2digits[] =
		{"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
		"Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
		string tens[] = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
		string hundred = "Hundred";		// 10 * 10
		string thousand = "Thousand";	// 1000
		string million = "Million";		// 1000 * 1000
		string billion = "Billion";		// 1000 * 1000 * 1000
		string scale_names[] = {thousand, million, billion};

		if(num == 0) return zero;

		next_digit = digits % digits_mask;
		if(next_digit < 20)
		{
			if(next_digit) {
				english.emplace_back(last2digits[next_digit]);
				digits -= next_digit;
			}
		}
		else {
			digits_mask = 10;
			next_digit = digits % digits_mask;
			if(next_digit) {
				english.emplace_back(last2digits[next_digit]);
				digits -= next_digit;
			}
			if(digits) {
				digits_mask *= 10;
				next_digit = digits % digits_mask / 10;
				if(next_digit) {
					english.emplace_back(tens[next_digit]);
					digits -= next_digit * 10;
				}
			}
		}

		if(digits) {
			// 100s
			digits_mask = 1000;
			digit_divisor = digits_mask/10;
			next_digit = (digits % digits_mask)/digit_divisor;
			if(next_digit) {
				english.emplace_back(hundred);
				english.emplace_back(last2digits[next_digit]);
				digits -= next_digit * digit_divisor;
			}
		}

		// Digits are 1000 and above
		// Now we can us a loop to scale up, but only for 2 loops before integer math overruns
		int x1000=1;
		for(int scale = 0; scale < 2; scale++) {
			bool need_scale = true;
			x1000 = x1000 * 1000;
			if(digits) {
				// 1000s get 2 digits
				digits_mask = 100 * x1000;

				digit_divisor = digits_mask/100;
				next_digit = (digits % digits_mask)/digit_divisor;
				if(next_digit < 20) {
					if(next_digit) {
						english.emplace_back(scale_names[scale]);
						need_scale = false;
						english.emplace_back(last2digits[next_digit]);
					}
					digits -= next_digit * digit_divisor;
				}
				else {
					// next_digit is >= 20
					// isolate the 1's digit
					next_digit = next_digit % 10;
					if(next_digit) {
						english.emplace_back(scale_names[scale]);
						need_scale = false;
						english.emplace_back(last2digits[next_digit]);
						digits -= next_digit * digit_divisor;
					}
					if(digits) {
						//digits_mask *= 10;
						digit_divisor = digits_mask/10;
						next_digit = (digits % digits_mask)/digit_divisor;
						if(next_digit) {
							if(need_scale)
								english.emplace_back(scale_names[scale]);
							english.emplace_back(tens[next_digit]);
							digits -= next_digit * digit_divisor;
						}
					}
				}
			}

			if(digits) {
				// 100s place remaining
				digits_mask = 1000 * x1000;
				digit_divisor = digits_mask/10;
				next_digit = (digits % digits_mask)/digit_divisor;
				if(next_digit) {
					if(need_scale)
						english.emplace_back(scale_names[scale]);
					english.emplace_back(hundred);
					english.emplace_back(last2digits[next_digit]);
					digits -= next_digit * digit_divisor;
				}
			}
		}

		if(digits) {
			// Only Billions remaining
			next_digit = digits / 1000000000;
			english.emplace_back(scale_names[2]);
			english.emplace_back(last2digits[next_digit]);
		}

		//cout << "Converting " << num << " = '";
		for(auto rit=rbegin(english); rit!=rend(english); ) {
			//cout << *rit << " ";
			result += *rit;

			if(++rit !=rend(english))
				result += " ";
		}
		//cout << "'" << endl;

		return result;
	}

};


/*
 *    Numbers
 * ------------
 * 0 - 19    			l2[0]		last2digts[0 - 19]
 * 20 - 99				l2[1]		tens[0 - 9] + last2digits[0 - 9]
 *
 * h00 - h99:			hXX
 * 100 - 119			h[0]		last2digits[1] + hundred + last2digits[0 - 19]
 * 120 - 199			h[1]		last2digits[1] + hundred + tens[0 -9] + last2digits[0 - 9]
 * 200 - 219			h[2]		last2digits[2] + hundred + last2digits[0 - 19]
 * 220 - 299			h[3]		last2digits[2] + hundred + tens[0 -9] + last2digits[0 - 9]
 * ..4,5,..6,7,..8,9..,10,11,..12,13,..14,15,..16,17
 * 920 - 999			h[17]
 *
 * 						tXXX
 * 1000 - 9999			t[0]		last2digits[1-9] + thousand + hXX
 * 10,000 - 19,999		t[1]		last2digits[0 - 19] + thousand + hXX
 * 20,000 - 99,999		t[2]		tens[0 - 9] + last2digits[0 - 9]
 *
 * 						TXX.XXX
 * 100,000 - 999,999	hXX + hundred
 *
 *
 *
 */

int main() {
	cout << "https://leetcode.com/problems/integer-to-english-words/" << endl;

	Solution Num2Words;
	string result;

	result = Num2Words.numberToWords(50868);
	//result = Num2Words.numberToWords(100000);

	cout << "Result string: '" << result << "'" << endl;
	return 0;
}
