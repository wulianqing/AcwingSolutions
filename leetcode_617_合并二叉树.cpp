#include<iostream>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    void dfs(TreeNode* t1,TreeNode* t2){
        if(t1 == NULL && t2 == NULL)
            return;
        else if(t1 == NULL && t2 != NULL){
            t1 = t2;
            return;
        }
        else if(t1 != NULL && t2 == NULL)
            return;
        else{
            t1->val += t2->val;
            dfs(t1->left, t2->left);
            dfs(t1->right, t2->right);
            return;
        }
    }

public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        dfs(t1, t2);
        return t1;
    }
};
