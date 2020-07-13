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
    ListNode* reverseList(ListNode* head) {
        ListNode *my_list = NULL;
        if(head == NULL)
            return head;
        ListNode *back = head;
        ListNode *front = back->next;
        while(back != NULL){
            back->next = my_list;
            my_list = back;
            back = front;
            if(front != NULL)
                front = front->next;
            else
                break;
        }
        return my_list;
    }
};
ListNode* createList(){
    int num;
    cin >> num;
    if(num == -1)
        return NULL;
    ListNode *head = new ListNode(num);
    head->next = createList();
    return head;
}
int main(){
    ListNode *head = createList();
    Solution solu;
    ListNode *my_list = solu.reverseList(head);
    ListNode *temp = my_list;
    while (temp != NULL){
        cout << temp->val << ' ';
        temp = temp->next;
    }
    cout << endl;
    return 0;
}