#include<iostream>
#include<vector>
using namespace std;
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    void travelTree(Node* root,vector<int>& v){
        if(root == NULL)return;
        if(root->left != NULL)travelTree(root->left,v);
        v.push_back(root->val);
        if(root->right != NULL)travelTree(root->right,v);
    }

    Node* treeToDoublyList(Node* root) {
        if(root == NULL)return NULL;
        vector<int> v;
        travelTree(root,v);
        Node* my_list = new Node(0);//head, no meaning
        Node* cur_node = my_list;
        for(int i = 0;i<v.size();i++){
            Node* temp = new Node(v[i]);
            cur_node->right = temp;
            temp->left = cur_node;
            cur_node = cur_node->right;
        }
        cur_node->right = my_list->right;
        my_list->right->left = cur_node;
        return my_list->right;
    }
};