//============================================================================
// Name        : lego-blocks.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.hackerrank.com/challenges/lego-blocks/
//============================================================================

#include <bits/stdc++.h>
using namespace std;

/*
 * Lego Blocks
 *
You have an infinite number of 4 types of lego blocks of sizes given as (depth x height x width):

d	h	w
1	1	1
1	1	2
1	1	3
1	1	4
Using these blocks, you want to make a wall of height  and width . Features of the wall are:

- The wall should not have any holes in it.
- The wall you build should be one solid structure, so there should not be a straight vertical break across all rows of bricks.
- The bricks must be laid horizontally.

How many ways can the wall be built?

For example, the wall's height n=2 and its width m=3. Here are some configurations:

[ ][  ]  [  ][ ]
[     ]  [ ][  ]

[     ]  [ ][ ][ ]
[     ]  [       ]
 */

/*
 * Discussion Forum:
 *
I found the crux to this problem was to first figure out the number possible ways to configure a single row of a wall of width W.
From this, you can get the number of ways to configure a wall of with W and height H.

I call this function totalWalls(W, H)
Lets call the function for non-breakable walls (the question the problem asks for), unbreakableWalls(W, H).

We have a base case of
unbreakableWalls(1, H) = 1 for all H

There's a recurrence you can find between unbreakableWalls and totalWalls, but I won't spoil that since that's half the fun!

1) (a-b)%p = (a - b + p)%p

2) (a+b+c+d)%p = (a%p + b%p + c%p + d%p)%p;

//////
if F(i) represent the possibilities of laying down a row of
length i, then it should be intuitive that:
F(i) = F(i - 1) + F(i - 2) + F(i - 3) + F(i - 4)
since the possibilities of laying down a row of length i is the
possibility of laying down a row of length i - 1 and a
1x1 block + possibility of laying down a row of length i - 2
and a 1x2 block, and so on.
 */

int legoBlocks(int n, int m) {
    /*
     * Write your code here.
     */
    // n: an integer that represents the height of the wall
    // m: an integer that represents the width of the wall

}

int main() {
	cout << "https://www.hackerrank.com/challenges/lego-blocks/" << endl; 
	return 0;
}
