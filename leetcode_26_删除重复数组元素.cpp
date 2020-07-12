#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        if(nums.size() == 1)
            return 1;
        int left = 0, right = 1;
        while(right < nums.size()){
            if(nums[right] == nums[left])
                right++;
            else
                nums[++left] = nums[right++];
        }
        return left+1;
    }
};
int main(){
    vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    Solution solu;
    int length = solu.removeDuplicates(nums);
    for (int i = 0; i < length;i++)
        cout << nums[i]<<" ";
    cout << endl;
    return 0;
}