#include<iostream>
#include<vector>

using namespace std;


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int length_nums = nums.size();
        vector<int> ans;
        for(int i=0;i<length_nums;i++){
            for(int j=i+1;j<length_nums;j++){
                if(nums[i]+nums[j]==target){
                    ans.push_back(i);
                    ans.push_back(j);
                }
                //else continue;
            }
        }
        return ans;
    }
};

//main 
int main(){
    vector<int> nums;
    int target = 9;
    int example_nums [4]= {2,7,11,15};
    for(int i=0;i<nums.size();i++){
        nums.push_back(nums[i]);
    }
    Solution solution;
    vector<int> ans = solution.twoSum(nums,target);
    cout<<"["<<ans[0]<<","<<ans[1]<<"]"<<endl;
    return 0;
}