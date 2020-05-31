#include<iostream>
#include<vector>
using namespace std;

class Solution
{
public:
    //Solution 1
    void dfs_1(int i,int j,vector<vector<int> > grid,int cur_sum,int& max_sum){
        cur_sum += grid[i][j];
        if(cur_sum > max_sum)
            max_sum = cur_sum;
        if(i+1 < grid.size())
            dfs_1(i+1,j,grid,cur_sum,max_sum);
        if(j+1<grid[0].size())
            dfs_1(i,j+1,grid,cur_sum,max_sum);
    }
    int maxValue_1(vector<vector<int> >& grid){
        int max_sum = 0;
        if(grid.size()==0)  
            return 0;
        dfs_1(0,0,grid,0,max_sum);
        return max_sum;
    }

    //Solution 2
    int maxValue_2(vector<vector<int>>& grid){
        int row = grid.size();
        int col = grid[0].size();
        if(row == 0)
            return 0;
        vector<vector<int>> dp_table = vector<vector<int>>(row, vector<int>(col));
        dp_table[0][0] = grid[0][0];
        //exception
        if(row == 1 && col && 1)
            return dp_table[0][0];
        if(row == 1){
            int max_sum = 0;
            for (int i = 0; i < col;i++)
                max_sum += grid[0][i];
            return max_sum;
        }
        if(col == 1){
            int max_sum = 0;
            for (int i = 0; i < row;i++)
                max_sum += grid[i][0];
            return max_sum;
        }
        //init dp table
        for (int i = 1; i < col;i++)
            dp_table[0][i] = dp_table[0][i - 1] + grid[0][i];
        for (int i = 1; i < row;i++)
            dp_table[i][0] = dp_table[i - 1][0] + grid[i][0];
        //calculate dp table
        for (int i = 1; i < row;i++){
            for (int j = 1; j < col;j++)
                dp_table[i][j] = max(dp_table[i - 1][j], dp_table[i][j - 1]) + grid[i][j];
        }
        return dp_table[row - 1][col - 1];
    }
};

int main(){
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {14, 2, 1}};
    Solution solu;
    cout<<"Solution 1: max value = "<< solu.maxValue_1(grid)<<endl;
    cout<<"Solution 2: max value = "<< solu.maxValue_2(grid)<<endl;
    return 0;
}