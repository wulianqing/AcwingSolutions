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
    int counter;

private:
    void travelTree(TreeNode* root,int sum){
        if(root == NULL)
            return;
        counterPathOfCurrentNode(root, sum, 0);
        travelTree(root->left,sum);
        travelTree(root->right,sum);
    }
    void counterPathOfCurrentNode(TreeNode* root,int sum,int cur_sum){
        if(root == NULL)
            return;
        cur_sum += root->val;
        if(cur_sum == sum)
            counter++;
        counterPathOfCurrentNode(root->left, sum, cur_sum);
        counterPathOfCurrentNode(root->right, sum, cur_sum);
    }

public:
    int pathSum(TreeNode* root, int sum) {
        if (root == NULL)
            return 0;
        travelTree(root,sum);
        return counter;
    }
};
TreeNode* createTree(){
    int num;
    cin >> num;
    if(num == -1)
        return NULL;
    TreeNode *temp = new TreeNode(num);
    temp->left = createTree();
    temp->right = createTree();
    return temp;
}
int main(){
    TreeNode *root = createTree();
    Solution solu;
    cout<<solu.pathSum(root, 16)<<endl;
    return 0;
}