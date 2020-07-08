#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices,int fee) {
        int n = prices.size();
        //exception: n == 0 || 1
        if(n == 0 || n == 1)
            return 0;
        //dp[days][hold/unhold]: 将[hold/unhold]直接分出来,使用两个一维dp
        vector<int> hold(n);
        vector<int> unhold(n);
        //init: i == 0
        hold[0] = -prices[0];
        unhold[0] = 0;
        //start with 1
        int ans = max(hold[0],unhold[0]);
        for (int i = 1; i < n; i++)
        {
            hold[i] = max(hold[i - 1], unhold[i - 1] - prices[i]);
            unhold[i] = max(unhold[i - 1], hold[i - 1] + prices[i] - fee);
            if(max(hold[i],unhold[i])>ans)
                ans = max(hold[i], unhold[i]);
        }
        return ans;
    }
};
int main(){
    vector<int> prices = {1, 3, 2, 8, 4, 9};
    int fee = 2;
    Solution solu;
    cout << solu.maxProfit(prices,fee) << endl;
    return 0;
}