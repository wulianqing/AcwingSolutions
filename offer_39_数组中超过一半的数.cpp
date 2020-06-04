#include<iostream>
#include<vector>
#include<set>
using namespace std;
class Solution
{
public:
    int majorityElement(vector<int>& nums) {
        multiset<int> my_set;
        for(int i = 0;i<nums.size();i++){
            my_set.insert(nums[i]);
            //cout << my_set.count(nums[i]) << endl;
            if (my_set.count(nums[i]) > nums.size()/2)
                return nums[i];
        }
        return 0;
    }
};
int main(){
    vector<int> nums = {1, 2, 3, 2, 2, 2, 5, 4, 2};
    Solution solu;
    cout<<solu.majorityElement(nums)<<endl;
    return 0;
}