#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
void dfs(vector<vector<int>> & matrix, vector<vector<bool>> & visited, int row, int column, int i, int j, int path_max_num, int cur_length, int & max_length)
{
    if(!(i >= 0 && i < row && j >= 0 && j < column && visited[i][j] == 0 && matrix[i][j] > path_max_num))
        return;
    visited[i][j] = 1;
    path_max_num = matrix[i][j];
    cur_length++;
    if(cur_length > max_length)
        max_length = cur_length;
    //up, down, left, right
    dfs(matrix, visited, row, column, i - 1, j, path_max_num, cur_length, max_length);
    dfs(matrix, visited, row, column, i + 1, j, path_max_num, cur_length, max_length);
    dfs(matrix, visited, row, column, i, j - 1, path_max_num, cur_length, max_length);
    dfs(matrix, visited, row, column, i, j + 1, path_max_num, cur_length, max_length);
    visited[i][j] = 0;
    path_max_num -= matrix[i][j];
    cur_length--;
    return;
}
int main(){
    int max_length = 0;
    vector<int> rowColumn;
    string s;
    cin >> s;
    string temp;
    stringstream input(s);
    while(getline(input,temp,',')){
        rowColumn.push_back(stoi(temp));
    }
    int row = rowColumn[0], column = rowColumn[1];
    vector<vector<int>> matrix(row, vector<int>(column));
    for (int i = 0; i < row;i++){
        string s;
        cin >> s;
        stringstream input(s);
        string temp;
        int j = 0;
        while (getline(input, temp, ','))
            matrix[i][j++] = stoi(temp);
    }
    vector<vector<bool>> visited(row, vector<bool>(column,false));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column;j++){
            //dfs
            dfs(matrix, visited, row, column, i, j, 0, 0, max_length);
        }
    }
    cout << max_length << endl;
    return 0;
}