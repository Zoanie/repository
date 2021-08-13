//============================================================================
// Name        : open-the-lock.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/open-the-lock/
//============================================================================

#include <iostream>
#include <set>
#include <queue>
#include <deque>

using namespace std;

/*
You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'.
The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning
one wheel one slot.

The lock initially starts at '0000', a string representing the state of the 4 wheels.

You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning
and you will be unable to open it.

Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to
open the lock, or -1 if it is impossible.

Example 1:
Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
Output: 6
Explanation:
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".

Example 2:
Input: deadends = ["8888"], target = "0009"
Output: 1
Explanation:
We can turn the last wheel in reverse to move from "0000" -> "0009".

Example 3:
Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
Output: -1
Explanation:
We can't reach the target without getting stuck.

Example 4:
Input: deadends = ["0000"], target = "8888"
Output: -1

Constraints:
	o 1 <= deadends.length <= 500
	o deadends[i].length == 4
	o target.length == 4
	o target will not be in the list deadends.
	o target and deadends[i] consist of digits only.
 */
class Solution {
public:
    set<string> deadendsDB;
    set<string> seenDB;
    // the leetcode.com solution uses java which implements a queue that can be iterated over.  The std library queue can not be iterated over!
    queue<string> combinationsQ;

    int openLock(vector<string>& deadends, string target) {
    	const string crossout = "X";

        for(auto& de : deadends) {
        	deadendsDB.emplace(de);
        }
        /*
        cout << "Deadends DB: ";
        for(auto& elem : deadendsDB) {
        	cout << elem << ", ";
        }
        cout << endl;
        */

        combinationsQ.emplace("0000");
        combinationsQ.emplace(crossout);
        /*
        combinations.emplace_back(crossout);
        combinations.emplace_back("0001");
        combinations.emplace_back("0002");
        combinations.emplace_back("0003");
        combinations.emplace_back(target);
        combinations.emplace_back("0004");
        combinations.emplace_back("0005");
		auto test = combinations.front();

        for(auto it=cbegin(combinations); it != cend(combinations); ++it) {
        	if(*it == crossout)
        		cout << "found crossout indicator" << endl;
        	else
        		cout << "found " << *it << endl;
        }
        */

        seenDB.emplace("0000");
        /*
        if(end(seenDB) != seenDB.find("0000"))
        {
        	cout << "The seenDB does have combo '0000'" << endl;
        }
        */

    	int turns = 0;
    	int tests = 0;
        while(!combinationsQ.empty()) {
        	auto combo = combinationsQ.front();
        	combinationsQ.pop();
    		//cout << "pop combo " << combo << endl;
    		if(combo == crossout) {
    			//cout << "crossout!" << endl;
    			turns++;
    			auto peek = combinationsQ.front();
    			if(peek != crossout)
    			{
    				combinationsQ.emplace(crossout);
    			}
    		}
    		else if(combo == target) {
    		    //printf("Found combination %s with minimum %d turns, using %d tests\n", combo.c_str(), turns, tests);
    		    return turns;
    		}
    		else if(end(deadendsDB) == deadendsDB.find(combo)) {
    			for(int i=0; i<4; i++) {
    				// move each of the four digits in the combination -1 & +1
    				for(int d = -1; d <= 1; d+=2) {
    					// allow digit to move from 0 to 9 to 1
    					int y = ((combo[i] - '0') + d + 10) % 10;
    					string test_combo = combo.substr(0, i) + (to_string(y)) + combo.substr(i+1);
    					//printf("d=(%d), y=(%d), ", d, y);
    					//cout << test_combo << " | " << flush;

    					auto it = seenDB.find(test_combo);
    			        if(it == end(seenDB)) {
    			        	//cout << "Adding combo" << test_combo << endl;
    			        	tests++;
    			        	seenDB.emplace(test_combo);
    	    				combinationsQ.emplace(test_combo);
    			        }
    				}
    				//cout << endl;
    			}
    		}
        }

        return -1;
    }
};

vector<string> Ex1_deadends {"0201","0101","0102","1212","2002"};
string Ex1_target = "0202";

vector<string> Ex2_deadends {"8887","8889","8878","8898","8788","8988","7888","9888"};
string Ex2_target = "8888";
int main() {
	cout << "https://leetcode.com/problems/open-the-lock/" << endl;
	Solution OpenTheLock;
	int numTurns = OpenTheLock.openLock(Ex2_deadends, Ex2_target);
	printf("Opened the lock in %d turns\n", numTurns);

	return 0;
}
