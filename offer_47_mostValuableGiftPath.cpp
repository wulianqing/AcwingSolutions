#include<iostream>
#include<vector>
using namespace std;

class Solution
{
public:
    void dfs(int i,int j,vector<vector<int> > grid,int cur_sum,int& max_sum){
        cur_sum += grid[i][j];
        if(cur_sum > max_sum)
            max_sum = cur_sum;
        if(i+1 < grid.size())
            dfs(i+1,j,grid,cur_sum,max_sum);
        if(j+1<grid[0].size())
            dfs(i,j+1,grid,cur_sum,max_sum);
    }
    int maxValue(vector<vector<int> >& grid){
        int max_sum = 0;
        if(grid.size()==0)  
            return 0;
        else{
            dfs(0,0,grid,0,max_sum);
            return max_sum;
        }
    }
};

int main(){
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {14, 2, 1}};
    Solution solu;
    cout<<"max value: "<< solu.maxValue(grid)<<endl;
    return 0;
}