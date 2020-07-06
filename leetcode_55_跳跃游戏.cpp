#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.size()==1)
            return true;
        vector<bool> dp(nums.size());
        for (int i = 0; i < nums.size();i++)
            dp[i] = false;
        dp[nums.size() - 1] = true;
        for (int i = nums.size() - 2; i >= 0; i--){
            for (int j = i + nums[i]; j > i;j--){
                if(dp[j] == true)
                    dp[i] = true;
            }
        }
        return dp[0];
    }
};

int main(){
    vector<int> nums1 = {2, 3, 1, 1, 4};
    vector<int> nums2 = {3, 2, 1, 0, 4};
    Solution solu;
    if(solu.canJump(nums1))
        cout << "nums 1 can jump" << endl;
    else
        cout << "nums 1 can not jump" << endl;
    if(solu.canJump(nums2))
        cout << "nums 2 can jump" << endl;
    else
        cout << "nums 2 can not jump" << endl;
    return 0;
}