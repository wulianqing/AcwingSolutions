#include<iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *my_head = new ListNode(0);
        my_head->next = head;
        ListNode *back = my_head;
        ListNode *front = head;
        for (int i = 0; i < n;i++)
            front = front->next;
        while(front != NULL){
            back = back->next;
            front = front->next;
        }
        ListNode *temp = back->next;
        back->next = temp->next;
        delete temp;
        return my_head->next;
    }
};