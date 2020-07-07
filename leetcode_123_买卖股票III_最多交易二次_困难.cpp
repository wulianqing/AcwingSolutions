#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {        
        int days = prices.size();
        //int[days+1][3][2]
        vector<vector<vector<int>>> dp(days, vector<vector<int>> (3, vector<int>(2)));
        //
        for (int i = 0; i < days;i++){
            //exception: i-1 == -1
            if(i == 0){
                dp[0][0][0] = dp[0][0][1] = dp[0][1][0]\
                 = dp[0][1][1] = dp[0][2][0] = dp[0][2][1] = 0;
            }
            //状态转移: for k : 3,但很少,直接手动写出即可
            else{
                
            }
        }
    }
};

int main(){
    Solution solu;
    vector<int> prices = {3,2,6,5,0,3};
    cout << solu.maxProfit(prices) << endl;
    return 0;
}