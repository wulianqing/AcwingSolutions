#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {        
        int length = prices.size();
        //exception
        if(length == 0 || length == 1)
            return 0;
        vector<int> dp1(length,0);
        vector<int> dp2(length,0);
        
        //calculate dp1: O(n^2)
        for (int i = 1; i < length;i++){
            for (int j = i - 1; j >= 0;j--){
                if(prices[j] < prices[i]){
                    dp1[i] = dp1[j] + prices[i] - prices[j];
                    break;
                }
            }
        }
        //calculate dp2:O(n^2)
        for (int i = 1; i < length;i++){
            if(dp1[i] != 0){
                int found_less = 0;
                int max_first_trade = 0;
                //find more than prices[i]
                for (int j = i - 1; j >= 0;j--){
                    if(prices[j] < prices[i]){
                        found_less = 1;
                        continue;
                    }
                    if (found_less == 1 && prices[j] > prices[i])
                    {
                        if(dp1[j] > max_first_trade)
                            max_first_trade = dp1[j];
                    }
                }
                if(max_first_trade != 0)
                    dp2[i] = max_first_trade + dp1[i];
            }
        }
        //find max
        int max = 0;
        for (int i = 0; i < length;i++){
            if(dp1[i] > max)
                max = dp1[i];
            if(dp2[i] > max)
                max = dp2[i];
        }
        return max;
    }
};

int main(){
    Solution solu;
    vector<int> prices = {3,2,6,5,0,3};
    cout << solu.maxProfit(prices) << endl;
    return 0;
}