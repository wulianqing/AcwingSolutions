#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> dp(target + 1,0);
        dp[0] = 1;
        if(target == 0)
            return 0;
        for (int i = 1; i <= target; i++)
            for (int j = 0; j < nums.size();j++)
                if(i - nums[j] >= 0)
                    dp[i] += dp[i - nums[j]];
        return dp[target];
    }
};
int main(){
    vector<int> nums = {3, 33, 333};
    int target = 10000;
    Solution solu;
    cout << solu.combinationSum4(nums, target) << endl;
    return 0;
}