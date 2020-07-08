#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int rob(vector<int>& nums){
        vector<int> nums1;
        vector<int> nums2;
        for (int i = 0; i < nums.size() - 1;i++){
            nums1.push_back(nums[i]);
            nums2.push_back(nums[i + 1]);
        }
        return max(subRob(nums1), subRob(nums2));
    }
    int subRob(vector<int> nums){
        vector<int> dp(nums.size());
        if(nums.size() == 0)return 0;
        if(nums.size() == 1)return nums[0];
        int ans = max(nums[0],nums[1]);
        int max = nums[0];
        for (int i = 0; i < nums.size(); i++)
        {
            //exception: i == 0, i == 1
            if(i == 0)
                dp[i] = nums[0];
            else if(i == 1)
                dp[i] = nums[1];
            else{
                dp[i] = max + nums[i];
                if(dp[i-1] > max)
                    max = dp[i-1];
                if(dp[i] > ans)
                    ans = dp[i];
            }
        }
        return ans;
    }
};
int main(){
    Solution solu;
    vector<int> nums = {1,2,3,1};
    cout << solu.rob(nums) << endl;
    return 0;
}