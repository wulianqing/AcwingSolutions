#include<iostream>
#include<vector>
using namespace std;

class Solution
{
public:
    int uniquePaths(int m, int n) {
        //exception
        if(m == 1 || n == 1)
            return 1;
        vector<vector<int>> dp(m, vector<int>(n));
        //init m == 1 || n == 1
        for(int i = 0; i < n;i++)
            dp[0][i] = 1;
        for (int i = 0; i < m;i++)
            dp[i][0] = 1;
        for (int i = 1; i < m;i++){
            for (int j = 1; j < n;j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
        return dp[m - 1][n - 1];
    }
};

int main(){
    Solution solu;
    //cout << solu.Cmn(6, 2) << endl;
    int m, n;
    while (cin>>m>>n){
        cout << solu.uniquePaths(m, n) << endl;
    }
    return 0;
}