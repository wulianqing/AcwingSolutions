#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int lengthOfLIS(vector<int>& nums) {
        //exception: nums.size() == 0 || 1
        if(nums.size() == 0)
            return 0;
        if(nums.size() == 1)
            return 1;
        int max = 1;
        vector<int> dp(nums.size(), 1);
        for (int i = 1; i < nums.size();i++){
            int max_before_length = 0;
            int max_before_j = -1;
            for (int j = i - 1; j >= 0;j--){
                //可以改成从0到i-1 更新最大的 就不用多设置两个变量
                //find nums[j] < nums[i] && max nums[j]
                if (nums[j] < nums[i])
                {
                    if(dp[j] > max_before_length){
                        max_before_j = j;
                        max_before_length = dp[j];
                    }
                }
            }
            if(max_before_j != -1){
                    dp[i] = dp[max_before_j] + 1;
                    if(dp[i] > max)
                        max = dp[i];
                    continue;
                }
        }
        return max;
    }
};
int main(){
    Solution solu;
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << solu.lengthOfLIS(nums) << endl;
    return 0;
}