#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
class Solution
{
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<int> path;
        vector<vector<int>> ans;
        unordered_map<vector<int>, bool> hm;
        dfs(nums, path, 0, ans, hm);
        return ans;
    }

    void dfs(vector<int>& nums,vector<int>& path,int cur_pos,vector<vector<int>>& ans,unordered_map<vector<int>, bool>& hm){
        //stop condition
        if(cur_pos >= nums.size())
            return;
        //if add cur_pos to visited
        if(nums[cur_pos] >= nums[path.size()-1])
            path.push_back(nums[cur_pos]);
        //if add path to ans
        
        /*
        if(hm.find(path) == hm.end()){
            hm.insert(make_pair(path, true));
            ans.push_back(path);
        }
        */
       
        ans.push_back(path);
        //visit rest positions
        for (int i = cur_pos + 1; i < nums.size();i++)
            dfs(nums, path, i, ans, hm);
        //pop cur_pos
        path.pop_back();
    }
};
int main(){
    vector<int> nums = {4, 6, 7, 7};
    Solution solu;
    vector<vector<int>> ans = solu.findSubsequences(nums);
    for (int i = 0; i < ans.size();i++){
        for (int j = 0; j < ans[i].size();j++)
            cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}