#include<iostream>
#include<vector>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> my_v;
        while (head != NULL){
            my_v.push_back(head->val);
            head = head->next;
        }
        int left = 0, right = my_v.size() - 1;
        while(left < right){
            if(my_v[left] == my_v[right])
                left++, right--;
            else
                break;
        }
        if(left >= right)
            return true;
        else
            return false;
    }
};