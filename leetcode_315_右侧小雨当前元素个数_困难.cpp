#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    vector<int> countSmaller(vector<int>& nums) {
        if(nums.size() == 0)
            return nums;
        if(nums.size() == 1)
            return vector<int>(1, 0);
        vector<int> dp(nums.size(), 0);
        for (int i = nums.size() - 2; i >= 0; i--)
        {
            int counter = 0;
            for (int j = nums.size() - 1; j > i; j--)
            {
                if(nums[j] < nums[i])
                    counter++;
            }
            dp[i] = counter;
        }
        return dp;
    }
};
int main(){
    vector<int> nums = {5, 2, 6, 1};
    Solution solu;
    vector<int> dp = solu.countSmaller(nums);
    for (int i = 0; i < nums.size(); i++)
        cout << dp[i] << endl;
    return 0;
}