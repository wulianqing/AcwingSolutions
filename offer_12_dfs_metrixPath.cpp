#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

bool dfs(char **metrix, int **visited, int row, int col, int i, int j, std::string word,int curr_length_path, int length_word)
{
    //stop
    if(curr_length_path == length_word)
        return true;

    bool found = false;

    //right
    if(j+1 < col && word[curr_length_path] == metrix[i][j+1] && visited[i][j+1] == 0){
        visited[i][j + 1] = 1;
        curr_length_path++;
        found = dfs(metrix, visited, row, col, i, j + 1, word, curr_length_path, length_word);
        if (found == true)
            return true;
        else{
            curr_length_path--;
            visited[i][j + 1] = 0;
        }
    }
    

    //down
    if(i+1 < row && word[curr_length_path] == metrix[i+1][j] && visited[i+1][j] == 0){
        visited[i+1][j] = 1;
        curr_length_path++;
        found =  dfs(metrix, visited, row, col, i+1, j, word, curr_length_path, length_word);
        if (found == true)
            return true;
        else{
            curr_length_path--;
            visited[i+1][j] = 0;
        }
    }
    

    //left
    if(j-1 >= 0 && word[curr_length_path] == metrix[i][j-1] && visited[i][j-1] == 0){
        visited[i][j - 1] = 1;
        curr_length_path++;
        found =  dfs(metrix, visited, row, col, i, j - 1, word, curr_length_path, length_word);
        if (found == true)
            return true;
        else{
            curr_length_path--;
            visited[i][j -1] = 0;
        }
    }
    
    //up
    if(i-1 >= 0 && word[curr_length_path] == metrix[i-1][j] && visited[i-1][j] == 0){
        visited[i-1][j] = 1;
        curr_length_path++;
        found =  dfs(metrix, visited, row, col, i-1, j, word, curr_length_path, length_word);
        if (found == true)
            return true;
        else{
            curr_length_path--;
            visited[i-1][j] = 0;
        }
    }
    

    //not found
        return false;
}

int main(){
    //build metrix 
    int row, col;
    cin >> row >> col;
    char **metrix = new char *[row];
    for (int i = 0; i < row;i++){
        metrix[i] = new char[col];
    }

    //input metrix
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col;j++){
            cin>>metrix[i][j];
        }
    }

    //build visited metrix
    int ** visited = new int *[row];
    for (int i = 0; i < row;i++){
        visited[i] = new int[col];
    }
    //init visited:0
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col;j++){
            visited[i][j] = 0;
        }
    }

    //input the search word
    std::string word;
    cin >> word;
    int length_word = word.size();

    /* 
    loop: find the begin position
        in loop: find if there is the path
        stop condition: length of the path
        check out the next step(restrain: should in the metrix & visited == 0 & is next value)
        including 4 directions
    if(path was found) true
    */
    for (int i = 0; i < row;i++){
        for (int j = 0; j < col;j++){
            //begin position
            if(word[0] == metrix[i][j]){
                //init
                //init visited:0
                for (int i = 0; i < row; i++)
                {
                    for (int j = 0; j < col;j++){
                        visited[i][j] = 0;
                    }
                }
                visited[i][j] = 1;
                int curr_length_path = 1;
                if(dfs(metrix, visited, row, col, i, j, word, curr_length_path, length_word))//return 1/0
                {
                    cout << "found" << endl;
                    return 0;   
                }   
            }
        }
    }
    cout << "not found" << endl;
    return 0;
}