#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;

struct cmp{
    bool operator()(const string & a,const string & b){
        return a + b > b + a;
    }
};

class Solution
{
public:
    
    string minNumber(vector<int>& nums) {
        priority_queue<string,vector<string>,cmp> pq;
        for(int i = 0;i < nums.size();i++)
            pq.push(to_string(nums[i]));
        string ans;
        for(int i = 0;i<nums.size();i++){
            ans += pq.top();
            pq.pop();
        }
        cout << ans << endl;
        return ans;
    }
};

int main(){
    vector<int> nums = {30, 5, 34, 3, 9};
    Solution solu;
    solu.minNumber(nums);
    return 0;
}