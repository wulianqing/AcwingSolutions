#include<iostream>
#include<vector>
using namespace std;
int main(){
    //input
    vector<int> quantity(5);
    for (int i = 0; i < 5;i++){
        int num;
        cin >> num;
        quantity[i] = num;
    }
    int sum;
    cin >> sum;
    //dp
    vector<vector<int>> dp(sum + 1, vector<int>(6,0));
    dp[0] = {0, quantity[0], quantity[1], quantity[2], quantity[3], quantity[4]};
    //calculate dp
    for (int i = 1; i <= sum;i++){
        int max_ways = 0;
        int value = 1;
        //1
        if(i - 1 >= 0)
            if(dp[i-1][1] > 0)
                if(dp[i - 1][0] > max_ways){
                    max_ways = dp[i - 1][0];
                    value = 1;
                }

        //3
        if(i - 3 >= 0)
            if(dp[i-3][2] > 0)
                if(dp[i - 3][0] > max_ways){
                    max_ways = dp[i - 3][0]; 
                    value = 3;
                }
                    
        //7
        if(i - 7 >= 0)
            if(dp[i-7][3] > 0)
                if(dp[i - 7][0] > max_ways){
                    max_ways = dp[i - 7][0];
                    value = 7;
                }

        //11
        if(i - 11 >= 0)
            if(dp[i-11][4] > 0)
                if(dp[i - 11][0] > max_ways)
                {
                    max_ways = dp[i - 11][0];
                    value = 11;
                }

        //13
        if(i - 13 >= 0)
            if(dp[i-13][5] > 0)
                if(dp[i - 13][0] > max_ways){
                    max_ways = dp[i - 13][0];
                    value = 13;
                }
        dp[i][0] = max_ways + 1;
        for (int j = 1; j <= 5;j++)
            dp[i][j] = dp[i - value][j];
        switch (value)
        {
        case 1:
            dp[i][1]--;
        case 3:
            dp[i][2]--;
        case 7:
            dp[i][3]--;    
        case 11:
            dp[i][4]--;
        case 13:
            dp[i][5]--;
        }  
    }
    cout << dp[sum][0] << endl;
    return 0;
}