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
    void dfs(TreeNode* node,int cur_sum,int sum,vector<int> v,vector<vector<int> > &ans){
        if(node == NULL){
            //cout<<"null: return"<<endl;
            return;
        }
        else{
            v.push_back(node->val);
            cur_sum += node->val;
            //cout<<"push: "<<node->val<<"\tcur_sum: "<<cur_sum<<endl;
            if(cur_sum == sum && node->left == NULL && node->right == NULL){
                ans.push_back(v);
                //cout<<"found a path, push into ans"<<endl;
            }
            dfs(node->left,cur_sum,sum,v,ans);
            dfs(node->right,cur_sum,sum,v,ans);
            //v删除最后
            //cur_sum减掉最后
            v.erase(v.begin()+v.size()-1);
            cur_sum -= node->val;
            //cout<<"pop: "<<node->val<<"\tcur_sum: "<<cur_sum<<endl;
        }
    }

    vector<vector<int> > pathSum(TreeNode* root, int sum) {
        
        int cur_sum = 0;
        vector<vector<int> > ans;
        vector<int> v;
        dfs(root,cur_sum,sum,v,ans);
        return ans;
    }
};