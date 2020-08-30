#include<iostream>
#include<vector>
using namespace std;

//矩阵 每行从左往右递增，每列从上到下递增，找target number
bool findMatrixNum(vector<vector<int>>& matrix, int number) {
    int i = matrix.size() - 1, j = 0;
    while(i >= 0 && j < matrix[0].size())
    {
        if(matrix[i][j] > number) i--;
        else if(matrix[i][j] < number) j++;
        else return true;
    }
    return false;
}

int main(){
    
}