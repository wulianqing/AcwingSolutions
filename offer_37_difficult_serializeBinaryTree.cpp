#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<sstream>
using namespace std;
//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
class Codec {
public:
    void tree2Vector(TreeNode* root,vector<string> & v){
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int num_cur_layer = q.size();
            for(int i = 0;i<num_cur_layer;i++){
                TreeNode* temp = q.front();
                q.pop();
                if(temp == NULL){
                    v.push_back("null");
                    continue;
                }
                else{
                    v.push_back(to_string(temp->val));
                    q.push(temp->left);
                    q.push(temp->right);
                }
            }
        }
        return;        
    }

    TreeNode* createTree2(string val,vector<string> v){
        if(val == "null")
            return nullptr;
        
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        vector<string> v;
        tree2Vector(root,v);
        for (vector<string>::iterator it = v.begin()+v.size()-1; *it == "null" && it != v.begin();it--)
            v.erase(it);
        //output
        cout << "[";
        for (int i = 0; i < v.size() - 1; i++)
            cout << v[i] << ',';
        cout << v[v.size()-1] << "]" << endl;
        return s;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> v = string2vector(data);
        static int sta_i;
        TreeNode *root = createTree(v[sta_i]);
    }
};

vector<string> string2vector(string data){
    stringstream input(data.substr(1,data.size()-2));
    string temp;
    vector<string> v_data;
    while(getline(input,temp,','))v_data.push_back(temp);
    //for(int i = 0;i<v_data.size();i++)cout<<v_data[i]<<' ';
    //cout<<endl;
    return v_data;
}

TreeNode* createTree(){
    int input;
    cin >> input;
    if(input == 0)
        return nullptr;
    TreeNode *temp = new TreeNode(input);
    if(input >= 0 && input <= 9){
        temp->left = createTree();
        temp->right = createTree();
    }
    return temp;
}



int main(){
    //cout << "create tree (e.g. 1 2 0 0 3 4 0 0 5 0 0)" << endl;
    TreeNode *root = createTree();
    Codec solu;
    //string2vector("[1,2,3,null,null,4,5]");
    string s = solu.serialize(root);
    vector<string>  my_vector = string2vector("[1,2,3,null,null,4,5]");
    for (int i = 0; i < my_vector.size();i++)
        cout << my_vector[i] << ' ';
    cout << endl;
    return 0;
}
