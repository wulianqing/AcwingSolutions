#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
class Solution
{
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> my_map;
        int max_quantity = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            my_map[nums[i]]++;
            if(my_map[nums[i]] > max_quantity)
                max_quantity = my_map[nums[i]];
            if(max_quantity > nums.size() / 2)
                return nums[i];
        }
        return 0;
    }
};
int main(){
    vector<int> nums = {2, 2, 1, 2, 1, 2, 1};
    Solution solu;
    cout << solu.majorityElement(nums) << endl;
    return 0;
}