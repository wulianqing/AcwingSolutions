#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> dp(amount + 1);
        if(amount <= 0)
            return -1;
        dp[0] = 0;
        for (int i = 1; i <= amount;i++){
            //dp[i] = max dp[i - coin[j]] + 1
            int min_cur = INT_MAX;
            for (int j = 0; j < n;j++)
                if(i - coins[j] >= 0 && dp[i - coins[j]] < min_cur)
                    min_cur = dp[i - coins[j]];
            dp[i] = min_cur + 1;
        }
        return dp[amount];
    }
};
int main(){
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    Solution solu;
    cout << solu.coinChange(coins, amount) << endl;
    return 0;
}