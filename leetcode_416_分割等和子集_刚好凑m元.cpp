#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for (int i = 0; i < n;i++)
            sum += nums[i];
        if(sum % 2 == 1)
            return false;
        int target = sum / 2;
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));
        //init
        for (int i = 0; i < n;i++)
            dp[i][0] = true;
        for (int i = 1; i <= target;i++)
            if(i == nums[0])
                dp[0][i] = true;
        for (int i = 1; i < n;i++)
            for (int j = 1; j <= target;j++){
                if(j-nums[i] >= 0)
                    dp[i][j] = dp[i-1][j] || dp[i-1][j - nums[i]];
                else
                    dp[i][j] = dp[i - 1][j];
            }
        return dp[n - 1][target];
    }
};
int main(){
    vector<int> nums = {1, 5, 11, 5};
    Solution solu;
    cout << solu.canPartition(nums) << endl;
    return 0;
}