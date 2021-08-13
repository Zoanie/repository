//============================================================================
// Name        : reorder-data-in-log-files.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/reorder-data-in-log-files/
//============================================================================

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm> // for lexicographical_compare()

using namespace std;

/*
 *
 *
You have an array of logs.  Each log is a space delimited string of words.
For each log, the first word in each log is an alphanumeric identifier.  Then, either:
	o Each word after the identifier will consist only of lowercase letters, or;
	o Each word after the identifier will consist only of digits.
We will call these two varieties of logs letter-logs and digit-logs.
It is guaranteed that each log has at least one word after its identifier.

Reorder the logs so that all of the letter-logs come before any digit-log.
The letter-logs are ordered lexicographically ignoring identifier, with the identifier
used in case of ties.  The digit-logs should be put in their original order.
Return the final order of the logs.

Example 1:
Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]

Constraints:
0 <= logs.length <= 100
3 <= logs[i].length <= 100
logs[i] is guaranteed to have an identifier, and a word after the identifier.
 */

class Solution {
	map<string, string> letterLogMap;
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
    	vector<string> letters;

    	if(logs.size() <= 1)
    		return logs;
    	int lognum=0;
    	for(auto str : logs) {

    		printf("log[%d] = '%s'\n", lognum++, str.c_str());
    		if(str[0] == 'l')
    		{

    		}
    	}
    	return logs;
    }


};

// function to tokenize a string
vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

// https://leetcode.com/problems/reorder-data-in-log-files/discuss/849016/topic
vector<string> Andrii_reorderLogFiles(vector<string>& l)
{
	stable_sort(begin(l), end(l), [](auto & a, auto & b)
		{
			auto A = 1 + a.find(' '), B = 1 + b.find(' ');
			return a[A]>'@' && (b[B]<'@' || a.substr(A).append(a, 0, A) < b.substr(B).append(b, 0, B));
		});
	return l;
}

// https://leetcode.com/problems/reorder-data-in-log-files/discuss/837338/C%2B%2B-2-Solutions
vector<string> Zxspring_reorderLogFiles(vector<string>& logs) {
	auto it = stable_partition(logs.begin(),logs.end(),[](const string& s){
	  return isalpha(s[s.find(" ")+1]);
	});
	sort(logs.begin(),it,[](const string& s1, const string& s2){
	  string substring1 = s1.substr(s1.find(" ")+1);
	  string substring2 = s2.substr(s2.find(" ")+1);
	  return substring1==substring2?s1<s2: substring1<substring2;
	});
	return logs;
}

int main() {
	cout << "https://leetcode.com/problems/reorder-data-in-log-files/" << endl;

	vector<string> logData {"dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"};
	Solution RDLF;

	RDLF.reorderLogFiles(logData);

	return 0;
}
