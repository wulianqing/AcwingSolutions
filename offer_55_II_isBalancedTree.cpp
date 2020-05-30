#include<iostream>
#include<vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    
    //Solution 1
    int depth_1(TreeNode* node){
        if(node == NULL)return 0;
        return max(depth_1(node->left),depth_1(node->right))+1;
    }
    bool isBalanced_1(TreeNode* root) {
        //bool ans;
        if(root == NULL)return true;
        else if(abs(depth_1(root->left)-depth_1(root->right))>1) return false;
        else return isBalanced_1(root->left) && isBalanced_1(root->right);

    }


    //Solution 2: better performance
    //return value -1: not balanced
    int depth_2(TreeNode *root, bool & ans)
    {
        if(root == NULL)
            return 0;
    
        //left is balanced?
        //ans == false? return ans
        int left_depth = depth_2(root->left,ans);
        if(!ans)
            return 0;
        //right is balanced?
        //ans == false? return ans
        int right_depth = depth_2(root->right,ans);
        if (!ans)
            return 0;
        //if left & right are balanced && diff of depth >1: ans = false
        if(abs(left_depth - right_depth) > 1){
            ans = false;
            return 0;
        }
        //return ans
        return max(left_depth, right_depth) + 1;
    }

    
    bool isBalanced_2(TreeNode* root){
        bool ans = true;
        depth_2(root, ans);
            return ans;
    }
};

//create a tree
TreeNode* createTree(){
    int input;
    cin >> input;
    if(input == 0){
        return NULL;
    }
    else{
        TreeNode *temp = new TreeNode(input);
        temp->left = createTree();
        temp->right = createTree();
        return temp;
    }
}

int main(){
    TreeNode *root = createTree();
    Solution solu;
    if(solu.isBalanced_1(root))
        cout << "solution 1: is balanced" << endl;
    else
        cout << "solution 1: is not balanced" << endl;
    if(solu.isBalanced_2(root))
        cout << "solution 2: is balanced" << endl;
    else
        cout << "solution 2: is not balanced" << endl;
    return 0;
}