#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution
{
public:
    int findLHS(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        sort(nums.begin(),nums.begin() + n);
        int left = 0,mid = 0,right = 0;
        while(left <= right && right < n){
            //update ans
            if(nums[right] - nums[left] == 1 && right - left + 1 > ans)
                ans = right - left + 1;
            //update mid
            if(nums[right] != nums[left] && nums[right-1] == nums[left])
                mid = right;

            //move pointer
            //
            if(nums[right] - nums[left] <= 1)
                right++;
            //diff > 1: move left
            else
                left = mid;
        }
        return ans;
    }
};
int main(){
    vector<int> nums = {1,2,2,1};
    Solution solu;
    cout << solu.findLHS(nums) << endl;
    return 0;
}