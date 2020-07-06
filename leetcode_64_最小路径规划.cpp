#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        if(n == 1){
            int ans = 0;
            for (int i = 0; i < m;i++)
                ans += grid[i][0];
            return ans;
        }
        if(m == 1){
            int ans = 0;
            for (int i = 0; i < n;i++)
                ans += grid[0][i];
            return ans;
        }
        vector<vector<int>> dp(m, vector<int>(n));
        //init
        dp[0][0] = grid[0][0];
        for (int i = 1; i < n;i++)
            dp[0][i] = grid[0][i] + dp[0][i - 1];
        for (int i = 1; i < m;i++)
            dp[i][0] = grid[i][0] + dp[i - 1][0];
        //calculate dp
        for (int i = 1; i < m;i++){
            for (int j = 1; j < n;j++)
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
        }
        return dp[m - 1][n - 1];
    }
};

int main(){
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    Solution solu;
    cout << solu.minPathSum(grid) << endl;
    return 0;
}