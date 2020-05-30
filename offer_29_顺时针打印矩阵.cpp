#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    void printRound(int left,int right,int up,int down,vector<int> & ans,vector<vector<int> > matrix){
        if(left == right){
            for(int i = up;i<=down;i++){
                ans.push_back(matrix[i][right]);
                //left++,right--,up++,down--;
            }
            return;
        }
        if(up == down){
            for(int j = left;j<=right;j++){
                ans.push_back(matrix[up][j]);
                //left++,right--,up++,down--;
            }
            return;
        }
        for(int j=left;j<=right;j++)ans.push_back(matrix[up][j]);
        for(int i=up+1;i<=down;i++)ans.push_back(matrix[i][right]);
        for(int j=right-1;j>=left;j--)ans.push_back(matrix[down][j]);
        for(int i=down-1;i>=up+1;i--)ans.push_back(matrix[i][left]);
    }

    vector<int> spiralOrder(vector<vector<int> >& matrix) {
        vector<int> ans;
        //exception
        if(matrix.size()==0)
            return ans;
        int left = 0, up = 0;
        int right = matrix[0].size()-1;
        int down = matrix.size()-1;
        while(left<=right && up <= down){
            printRound(left,right,up,down,ans,matrix);
            left++,right--,up++,down--;
        }
        return ans;
    }
};

int main(){
    vector<vector<int> > matrix = vector<vector<int> >(3,(vector<int>(4)));
    int counter = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4;j++){
            matrix[i][j] = counter;
            counter++;
        }
    }
    Solution solu;
    vector<int> ans = solu.spiralOrder(matrix);
    for (int i = 0; i < ans.size();i++){
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}