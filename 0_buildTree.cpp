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
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {

    }
};


int main(){
    TreeNode *A;
    TreeNode *B;
    /* 
    build tree(dfs)
    input (end with '/')e.g.: "12##34##5##/"
    */
    string cur_input;
    queue<TreeNode *> que;
    for (int i = 0; i < cur_input.size();i++){
        
    }
}