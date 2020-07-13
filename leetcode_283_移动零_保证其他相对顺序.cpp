#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    void moveZeroes(vector<int>& nums) {
        if(nums.size() == 0 || nums.size() == 1)
            return;
        int back = 0;
        while(nums[back] != 0)
            back++;
        int front = back + 1;
        while (front < nums.size())
        {
            if(nums[front] != 0)
                nums[back++] = nums[front++];
            else
                front++;
        }
        while(back < nums.size())
            nums[back++] = 0;
        return;
    }
};
int main(){
    vector<int> nums = {1,0};
    Solution solu;
    solu.moveZeroes(nums);
    for (int i = 0; i < nums.size();i++)
        cout << nums[i] << ' ';
    cout << endl;
    return 0;
}