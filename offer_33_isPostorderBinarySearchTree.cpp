#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    bool verifyPostorder(vector<int>& postorder) {
        if(postorder.size() == 0 || postorder.size() == 1 || postorder.size() == 2)
            return true;
        //size >= 3
        int left_first = 0;
        int right_first = 0;
        while(postorder[right_first] < postorder[postorder.size()-1] && right_first < postorder.size()-2)right_first++;
        //only left tree
        if(right_first == postorder.size()-2 && postorder[right_first] < postorder[postorder.size()-1])right_first = -1;
        if(right_first == -1){
            if(postorder[postorder.size()-2] > postorder[postorder.size()-1])
                return false;
            vector<int> left_tree(postorder.begin(), postorder.begin() + postorder.size() - 1);
            return verifyPostorder(left_tree);
        }
        int left_last = right_first - 1;
        int right_last = postorder.size()-2;
        vector<int> right_tree(postorder.begin()+right_first,postorder.begin()+right_last + 1);
        //only right tree
        if(left_last < 0){
            if(postorder[postorder.size()-2] < postorder[postorder.size()-1])
                return false;
            return verifyPostorder(right_tree);
        }
        if(!(postorder[left_last] < postorder[postorder.size()-1] && postorder[postorder.size()-1] < postorder[right_last]))
            return false;
        vector<int> left_tree(postorder.begin()+left_first,postorder.begin()+left_last + 1);
        return verifyPostorder(left_tree) && verifyPostorder(right_tree);
    }
};

int main(){
    vector<int> postorder = {7,4,6,5};
    Solution solu;
    cout << solu.verifyPostorder(postorder) << endl;
    return 0;
}