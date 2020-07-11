#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;
class Solution
{
public:
    int findLHS(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        unordered_map<int, int> hm;
        for (int i = 0; i < n;i++)
            hm[nums[i]]++;
        for (unordered_map<int, int>::iterator it = hm.begin(); it != hm.end();it++){
            if(hm.find(it->first + 1) != hm.end())
                if(it->second + hm[it->first + 1] > ans)
                    ans = it->second + hm[it->first + 1];
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