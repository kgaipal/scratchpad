using namespace std;

#include <iostream>
#include <vector>

class MissingNumber
{
public:
    vector<int> findMissingNumber(vector<int> &nums) {
            vector<int> missingNumbers;

            // find all numbers which are not at their posiitions and if an numbner is 'n' then hold in memory and dont put anywhere
            // worst case: O(n); found second last number out of place with last number (last 2 swapped in position)

            int i = 0;
            while (i < nums.size())
            {
                // correct place, skip
                if (nums[i] == i + 1)
                {
                    i++;
                    continue;
                }

                // cant fit anywhere .. tombstone
                if (nums[i] < 1)
                {
                    i++;
                    continue;
                }

                // we will be swapping same number, make this found duplicate a tombstone
                if (nums[i] == nums[nums[i] - 1])
                {
                    nums[i] = 0;
                    i++;
                }
                else
                {
                    // find spot for correct one
                    swap(nums, i);
                }

            } // end-while

            /// iterate which one is missing
            for (int i = 0; i < nums.size(); i++)
            {
                if (nums[i] != i + 1)
                {
                    missingNumbers.push_back(i + 1);
                }
            }

            return missingNumbers;
        }

private:
    void swap(vector<int> & nums, int i)
        {
            int a = nums[i];
            int b = nums[a - 1];

            // swap
            nums[i] = b;
            nums[a - 1] = a;
        }
};

int main()
{
    // vector<int>v {4, 0, 3, 1};
    // vector<int>v {0, 2, 1, 4};
    // vector<int>v {8, 3, 5, 2, 4, 6, 0, 1};
    vector<int>v {2,3,1,8,2,3,5,1};
    MissingNumber a;

    vector<int> res = a.findMissingNumber(v);
    for (int i = 0 ; i < res.size(); i++)
    {
        std::cout << res[i] << ", ";
    }

    return 0;
}
