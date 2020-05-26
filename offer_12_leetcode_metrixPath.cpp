#include<vector>
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Solution
{
public:
    bool exist(vector<vector<char> >& board, string word) {
        //define variables & visited metrix
        int row = board.size();
        int col = board[0].size();
        int length_word = word.size();
        vector<vector<bool> > visited(row,vector<bool>(col,0));

        //exception: word.size() == 1

        /* 
        loop: find start position as root
        dfs:
        start with: length_cur_path = 1; 
        */    
        for(int i = 0;i<row;i++){
            for(int j =0;j<col;j++){
                //start position
                if(word[0] == board[i][j]){
                    //reinit visited metrix, length_cur_path
                    /*
                    for(int i=0;i<row;i++){
                        for(int j=0;j<col;j++){
                            visited[i][j] = 0;
                        }
                    }
                    */
                    visited[i][j] = 1;
                    int length_cur_path = 1;
                    //current start position can find the path?
                    if(dfs(board,visited,word,row,col,i,j,length_cur_path,length_word))
                        return true;
                    visited[i][j] = false;
                }
            }
        }
        return false;
    }

    bool dfs(vector<vector<char> > board,vector<vector<bool> > visited,string word,int row,int col,int i,int j,int length_cur_path,int length_word){
        //stop condition
        if(length_cur_path == length_word)
            return true;
        
        //recorder
        bool found = false;

        //find path
        //right
        if(j+1 < col && word[length_cur_path] == board[i][j+1] && visited[i][j+1] == 0){
            visited[i][j + 1] = 1;
            length_cur_path++;
            found = dfs(board, visited, word,row, col, i, j + 1, length_cur_path, length_word);
            if (found == true)
                return true;
            else{
                length_cur_path--;
                visited[i][j + 1] = false;
            }
        }

        //down
        if(i+1 < row && word[length_cur_path] == board[i+1][j] && visited[i+1][j] == 0){
            visited[i+1][j] = 1;
            length_cur_path++;
            found = dfs(board, visited, word, row, col, i+1, j, length_cur_path, length_word);
            if (found == true)
                return true;
            else{
                length_cur_path--;
                visited[i + 1][j] = false;
            }
        }

        //left
        if(j-1 >=0 && word[length_cur_path] == board[i][j-1] && visited[i][j-1] == 0){
            visited[i][j - 1] = 1;
            length_cur_path++;
            found = dfs(board, visited, word,row, col, i, j - 1, length_cur_path, length_word);
            if (found == true)
                return true;
            else{
                length_cur_path--;
                visited[i][j - 1] = false;
            }
        }

        //up
        if(i-1 >= 0 && word[length_cur_path] == board[i-1][j] && visited[i-1][j] == 0){
            visited[i-1][j] = 1;
            length_cur_path++;
            found = dfs(board, visited, word, row, col, i-1, j, length_cur_path, length_word);
            if (found == true)
                return true;
            else{
                length_cur_path--;
                visited[i-1][j] = false;
            }
        }

        //not found
        return false;
    }
};


int main(){
    //build metrix 
    int row, col;
    cin >> row >> col;
    vector<vector<char> > board(row,vector<char>(col,0));

    //input metrix
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col;j++){
            cin>>board[i][j];
        }
    }


    //input the search word
    std::string word;
    cin >> word;

    Solution obj_solu;
    if(obj_solu.exist(board, word))
        cout << "found" << endl;
    else
        cout << "not found" << endl;

    return 0;
}