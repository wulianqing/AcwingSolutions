#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        //exception: n == 0 || 1
        if(n == 0 || n == 1)
            return 0;
        //dp: 用4个一维dp来表示dp[days][交易剩余次数:0,1,2][持股与否:0,1]
        //分别为hold_0,hold_1,unhold_0,unhold_1 (因为hold_2不需要,unhold_2恒等于0)
        vector<int> hold_0(n);
        vector<int> hold_1(n);
        vector<int> unhold_0(n);
        vector<int> unhold_1(n);
        //init: i == 0, -1表示不可能的情况
        hold_1[0] = -prices[0];
        hold_0[0] = INT_MIN;
        unhold_0[0] = INT_MIN;
        unhold_1[0] = INT_MIN + prices[1];
        int ans = 0;
        for (int i = 1; i < n; i++)
        {
            hold_0[i] = max(hold_0[i - 1], unhold_1[i - 1] - prices[i]);
            hold_1[i] = max(hold_1[i - 1], -prices[i]);
            unhold_0[i] = max(unhold_0[i - 1], hold_0[i - 1] + prices[i]);
            unhold_1[i] = max(unhold_1[i - 1], hold_1[i - 1] + prices[i]);
            int max_i = max(max(hold_1[i],hold_0[i]),max(unhold_0[i],unhold_1[i]));
            if(max_i > ans)
                ans = max_i;
        }
        return ans;
    }
};

int main(){
    Solution solu;
    vector<int> prices = {7,6,4,3,1};
    cout << solu.maxProfit(prices) << endl;
    return 0;
}