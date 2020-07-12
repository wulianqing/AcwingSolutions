#include<iostream>
#include<vector>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    void addNode(ListNode*& p3,ListNode*& p){
        ListNode *temp = p;
        p = p->next;
        temp->next = nullptr;
        p3->next = temp;
        p3 = p3->next;
    }
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *p1 = l1;
        ListNode *p2 = l2;
        ListNode *my_list = new ListNode;
        ListNode *p3 = my_list;
        while(p1 != nullptr && p2 != nullptr){
            if(p1->val < p2->val)
                addNode(p3, p1);
            else
                addNode(p3, p2);
        }
        if(p1 != nullptr)
            p3->next = p1;
        else
            p3->next = p2;
        return my_list->next;
    }
};
int main(){
    ListNode *l1 = new ListNode;
    ListNode *l2 = new ListNode;
    ListNode *p1 = l1;
    ListNode *p2 = l2;
    vector<int> nums1 = {1, 1, 2, 4, 6};
    vector<int> nums2 = {2, 2, 5, 6, 7, 8, 10};
    for (int i = 0; i < nums1.size(); i++)
    {
        p1->next = new ListNode(nums1[i]);
        p1 = p1->next;
    }
    for (int i = 0; i < nums2.size(); i++)
    {
        p2->next = new ListNode(nums2[i]);
        p2 = p2->next;
    }
    Solution solu;
    ListNode *merged_list = solu.mergeTwoLists(l1->next, l2->next);
    for (ListNode *temp = merged_list; temp != nullptr;temp = temp->next)
        cout << temp->val << " ";
    cout << endl;
    return 0;
}
