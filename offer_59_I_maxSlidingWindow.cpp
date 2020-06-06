#include<iostream>
#include<vector>
#include<deque>
using namespace std;
class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;
        if(k == 1)
            return nums;
        deque<int> dq;
        int left = 0,right = 0;
        while(right < k){
            if(dq.empty())dq.push_back(nums[right++]);
            else{
                while(!dq.empty() && right < nums.size() && dq.back() < nums[right])
                    dq.pop_back();
                dq.push_back(nums[right++]);
            }
        }
        right--;
        //now: left == 0, right == k-1
        while(right < nums.size()){
            ans.push_back(dq.front());
            //check deque front 
            if(nums[left] == dq.front())
                dq.pop_front();
            left++;
            //update deque back
            right++;
            while(!dq.empty() && right < nums.size() && dq.back() < nums[right])
                dq.pop_back();
            if(right < nums.size())
                dq.push_back(nums[right]);
        }
        return ans;
    }
};

int main(){
    vector<int> nums_1 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> nums_2 = {9, 11};
    Solution solu;
    vector<int> ans = solu.maxSlidingWindow(nums_2, 2);
    for(auto num : ans)
        cout << num << " ";
    cout << endl;
    return 0;
}