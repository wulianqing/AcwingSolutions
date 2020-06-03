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
        //only left tree

        //only right tree

        //calculate left_first,right_first,left_last,right_last
        //build left tree & right tree

        //judge if left_root < cur_root && right_root > cur_root,if not:return false
        
        //recursion
        return verifyPostorder(left_tree) && verifyPostorder(right_tree);
    }
};

int main(){
    vector<int> postorder = {7,4,6,5};
    Solution solu;
    cout << solu.verifyPostorder(postorder) << endl;
    return 0;
}