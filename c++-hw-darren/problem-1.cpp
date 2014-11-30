/**
1.  You have a ladder n-steps in height.  You can either take one step
or two steps up the ladder at a time.  How can you find out all the
different combinations up the ladder?  Then figure out an algorithm that
will actually print out all the different ways up the ladder.  ie:
1,1,2,1,2,2... etc...

Sol:

This can be solved by dynamic programming but I was not able to come up with a
mathametical formula for any N because this I suspect can be done using permutations and
combinations. I tried some examples starting with n=1, n=2 ... to n=5 and it followed my
expectations.

Visualize each step as a dot '.' and we start at 'x' and finish at the last dot.

If we have only one step on the ladder, we have only one way to reach n=1 i.e.
    x . => x 1

If we have only two steps on the ladder, we have 2 ways to reach second (n=2) dot
    x . . => x 1 1
	     x 2

If we have 3 steps on the ladder, we have 3 ways to reach third (n=3) dot
    x . . . =>  x 1 1 1
		x 2   1
		x 1 2

If we have 4 steps on the ladder, we have 5 ways to reach fourth (n=4) dot
    x . . . . => x 1 1 1 1
		 x 2   1 1
		 x 2   2
		 x 1 1 2
		 x 1 2   1

If we have 5 steps on the ladder, we have 8 ways to reach fourth (n=5) dot
    x . . . . . => x 1 1 1 1 1
		   x 2   1 2
		   x 1 2   1
		   x 1 1 1 2
		   x 1 2   1 1
		   x 1 2   2
		   x 2   1 1 1
		   x 1 1 2   1

Observing the pattern, we see that steps for any step k is actually the sum of the ways we
could reach k-1 and k-2 steps i.e.

n=1  n=2  n=3  n=4  n=5 ...
 1    2    3    5    8

Hence we can compute say for nth step as the summation of all the steps it took for us to
reach n-1 and n-2 step. Like I said I was not able to get a mathematical formula using
permutation-combination so I cant back up with math proof that this will hold true for any
N step.

*/

#include <iostream>

// big-O for space: constant -- 4 variables only, good
// big-O for time: O(stepsInLadder) -- linear, good
int computeAllPermutationsToReachLadderTop(unsigned int stepsInLadder)
{
	unsigned int fn1 = 1;
	unsigned int fn2 = 2;

	if (stepsInLadder == 0) {
		return 0;
	} else if (stepsInLadder == 1) {
		return fn1;
	} else if (stepsInLadder == 2) {
		return fn2;
	}

	unsigned int fnN = fn2;

	// loop invariant: 3 <= i <= stepsInLadder and fnN == fn2
	for (unsigned int i = 3; i <= stepsInLadder; i++) {
		fnN = fn2 + fn1;

		// update progress of last two steps values so that we can compute future
		// step value
		fn1 = fn2;
		fn2 = fnN;
	}

	return fnN;
}

int main(/*no args*/)
{
    int stepsInLadder = 0;
    while (stepsInLadder < 0) {
	    std::cout << "Enter the steps in ladder (>0): " << std::endl;
	    std::cin >> stepsInLadder;
    }

    std::cout << "Total " << computeAllPermutationsToReachLadderTop()
	      << " ways to reach ladder top." << std::endl;

    return 0;
}
