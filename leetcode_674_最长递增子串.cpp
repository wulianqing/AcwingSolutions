#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        if(nums.size() == 1)
            return 1;
        int max_length = 1;
        vector<int> dp(nums.size(), 1);
        for (int i = 1; i < nums.size();i++){
            if(nums[i] > nums[i-1])
                dp[i] = dp[i - 1] + 1;
            if(dp[i] > max_length)
                max_length = dp[i];
        }
        return max_length;
    }
};
int main(){
    vector<int> nums1 = {2, 2, 2, 2};
    vector<int> nums2 = {1, 3, 5, 4, 7};
    Solution solu;
    cout << solu.findLengthOfLCIS(nums1) << endl;
    cout << solu.findLengthOfLCIS(nums2) << endl;
    return 0;
}