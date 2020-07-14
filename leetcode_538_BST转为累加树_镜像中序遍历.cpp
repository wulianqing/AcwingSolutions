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
    int cur_sum;
public:
    TreeNode* convertBST(TreeNode* root) {
        if(root == NULL)
            return NULL;
        convertBST(root->right);
        cur_sum += root->val;
        root->val = cur_sum; 
        convertBST(root->left);
        return root;
    }
};