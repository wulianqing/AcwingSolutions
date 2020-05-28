// INCLUDE HEADER FILES NEEDED BY YOUR PROGRAM
// SOME LIBRARY FUNCTIONALITY MAY BE RESTRICTED
// DEFINE ANY FUNCTION NEEDED
// FUNCTION SIGNATURE BEGINS, THIS FUNCTION IS REQUIRED

/* 
dfs: 
if found
right, down, left, up
not found
*/
int dfs(int i,int j,int rows,int columns,int **grid,int **visited){
    //found
    if(grid[i][j] == 9)return 1;
    //right
    if(j+1 < columns && visited[i][j+1] == 0 && (grid[i][j+1] == 1 || grid[i][j+1]==9)){
        //visit
        visited[i][j+1]=1;
        int found = 0;
        found = dfs(i,j+1,rows,columns,grid,visited);
        //found
        if(found == 1)return 1;
        //not found in this direction: continue
        else visited[i][j+1] = 0;
    }
    
    //down
    if(i+1 < rows && visited[i+1][j] == 0 && (grid[i+1][j] == 1 || grid[i+1][j]==9)){
        //visit
        visited[i+1][j]=1;
        int found = 0;
        found = dfs(i+1,j,rows,columns,grid,visited);
        //found
        if(found == 1)return 1;
        //not found in this direction: continue
        else visited[i+1][j] = 0;
    }
    
    //left
    if(j-1 >= 0 && visited[i][j-1] == 0 && (grid[i][j-1] == 1 || grid[i][j-1]==9)){
        //visit
        visited[i][j-1]=1;
        int found = 0;
        found = dfs(i,j-1,rows,columns,grid,visited);
        //found
        if(found == 1)return 1;
        else visited[i][j-1] = 0;
    }
    
    //up
    if(i-1 >= 0 && visited[i-1][j] == 0 && (grid[i-1][j] == 1 || grid[i-1][j]==9)){
        //visit
        visited[i-1][j]=1;
        int found = 0;
        found = dfs(i-1,j,rows,columns,grid,visited);
        //found
        if(found == 1)return 1;
        //not found in this direction: continue
        else visited[i-1][j] = 0;
    }
    return 0;
}


int isPath(int rows, int columns, int **grid)
{
    // WRITE YOUR CODE HERE
    //exception
    if(grid[0][0] == 0)return 0;
    
    //define metrix: visited 
    int **visited = new int*[rows];
    for(int i = 0;i < rows;i++){
        visited[i] = new int[columns];
    }
    //init visited
    for(int i = 0;i < rows;i++){
        for(int j = 0;j<columns;j++){
            visited[i][j] = 0;
        }
    }
    visited[0][0] = 1;
    return dfs(0,0,rows,columns,grid,visited);

}
// FUNCTION SIGNATURE ENDS