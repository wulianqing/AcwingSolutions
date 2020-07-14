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
    int dfs(TreeNode* root,int & max_distance){
        if(root == NULL)
            return 0;
        int left_ret = dfs(root->left,max_distance);
        int right_ret = dfs(root->right,max_distance);
        if(left_ret + right_ret > max_distance)
            max_distance = left_ret + right_ret;
        root->val = max(left_ret, right_ret) + 1;
        return root->val;
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        if(root == NULL)
            return 0;
        int max_distance = 0;
        dfs(root,max_distance);
        return max_distance;
    }
};