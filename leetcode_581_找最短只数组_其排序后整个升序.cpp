#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<int> right_min(n);
        vector<int> left_max(n);
        for (int i = n-1; i >= 0;i--){
            if(i == n-1)
                right_min[i] = nums[n-1];
            else
                right_min[i] = min(right_min[i + 1], nums[i]);
        }
        for (int i = 0; i < n;i++){
            if(i == 0)
                left_max[i] = nums[0];
            else
                left_max[i] = max(left_max[i - 1], nums[i]);
        }
        int i = 0, j = n - 1;
        while(i < n && nums[i] == right_min[i]){
            i++;
        }
        while (j >= 0 &&nums[j] == left_max[j]){
            j--;
        }
        if(j > i)
            return j - i + 1;
        else
            return 0;
    }
};
int main(){
    vector<int> nums = {2, 6, 4, 8, 10, 9, 15};
    Solution solu;
    cout << solu.findUnsortedSubarray(nums) << endl;
    return 0;
}