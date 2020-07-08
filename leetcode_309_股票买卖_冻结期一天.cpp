#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        //exception: n == 0 || 1 || 2([i-2])
        if(n == 0 || n == 1)
            return 0;
        if(n == 2){
            if(prices[1] > prices[0])
                return prices[1] - prices[0];
            else
                return 0;
        }
        //dp[days][hold/unhold]: 将[hold/unhold]直接分出来,使用两个一维dp
        vector<int> hold(n);
        vector<int> unhold(n);
        //init: i == 0 || 1
        hold[0] = -prices[0];
        hold[1] = max(hold[0],-prices[1]);
        unhold[0] = 0;
        unhold[1] = max(unhold[0], prices[1] - prices[0]);
        //start with 2
        int ans = max(max(hold[0], hold[1]), max(unhold[0], unhold[1]));
        for (int i = 2; i < n; i++)
        {
            hold[i] = max(hold[i - 1], unhold[i - 2] - prices[i]);
            unhold[i] = max(unhold[i - 1], hold[i - 1] + prices[i]);
            if(max(hold[i],unhold[i])>ans)
                ans = max(hold[i], unhold[i]);
        }
        return ans;
    }
};
int main(){
    vector<int> prices = {1, 2, 3, 0, 2};
    Solution solu;
    cout << solu.maxProfit(prices) << endl;
    return 0;
}