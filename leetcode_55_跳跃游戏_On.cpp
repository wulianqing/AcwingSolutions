#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    bool canJump(vector<int>& nums) {
        int max = 0;
        int block = nums[0];
        for (int i = 0; i < nums.size() && i <= max;i++)
        {
            int cur_max = i + nums[i];
            if(cur_max > max)
                max = cur_max;
        }
        if(max >= nums.size()-1)
            return true;
        else
            return false;
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