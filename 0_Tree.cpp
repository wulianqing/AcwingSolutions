#include<iostream>
#include<queue>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::string;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        return false;
    }
};

void createTree(TreeNode *&root){
    int ch_input;
    cin >> ch_input;
    //0: NULL
    if(ch_input == 0)
        return;
    
    else if(ch_input > 0){
        if(root == NULL){
            root = new TreeNode;
        }
        root->val = ch_input;
    }
    createTree(root->left);
    createTree(root->right);
    return;
}

//print tree with bfs
void printTreeBFS(TreeNode *root){
    queue<TreeNode *> que;
    que.push(root);
    while(!que.empty()){
        int que_size = que.size();
        for (int i = 0; i < que_size;i++){
            TreeNode *temp = que.front();
            que.pop();
            if(temp == NULL){
                cout << "# ";
                continue;
            }
            else if(temp->val == 0){    
                cout << "# ";
                continue;
            }
            else 
                cout << temp->val << " ";
            //push children
            que.push(temp->left);
            que.push(temp->right);
        }
        cout << endl;
    }
}

int main(){
    TreeNode *A = NULL;
    // TreeNode *B;
    /* 
    build tree(dfs)
    input e.g.: "1 2 3 0 0 4 5 0 0"
    */
    createTree(A);
    
    //check out
    printTreeBFS(A);

    return 0;
}