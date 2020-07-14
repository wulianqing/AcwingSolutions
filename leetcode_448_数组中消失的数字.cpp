#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution
{
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;
        if(nums.size() == 0)
            return ans;
        sort(nums.begin(), nums.begin() + n);
        int back = 0, front = 1;
        int counter = 0;
        if(nums[back] != 1)
            ans.push_back(1);
        while (front < n)
        {
            if(nums[back] == nums[front])
                counter++;
            else if(nums[back] + 1 != nums[front])
                for(int i = nums[back] + 1;i < nums[front];i++)
                    ans.push_back(i);
            back++, front++;
        }
        int cur_ans_size = ans.size();
        for (int i = 0; i < counter - cur_ans_size; i++)
            ans.push_back(i + (n - (counter - cur_ans_size) + 1));
        return ans;
    }
};
int main(){
    vector<int> nums = {1,1};
    Solution solu;
    vector<int> ans = solu.findDisappearedNumbers(nums);
    for (int i = 0; i < ans.size();i++)
        cout << ans[i] << ' ';
    cout << endl;
    return 0;
}