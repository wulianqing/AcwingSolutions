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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *pA = headA;
        ListNode *pB = headB;
        bool reachA = false;
        bool reachB = false;
        while (pA != NULL && pB != NULL){
            if(pA->next == NULL && reachA == false){
                pA = headB;
                reachA = true;
            }
            if (pB->next == NULL && reachB == false){
                pB = headA;
                reachB = true;
            }
            if(pA == pB && reachA == true && reachB == true)
                return pA;
            pA = pA->next;
            pB = pB->next;
        }
        return NULL;
    }
};
int main(){
    //headA:   4,1,8,4,5
    //headB: 5,6,1,8,4,5
    //相交于:       8
    ListNode *headA = new ListNode(4);
    ListNode *tempA = headA;
    tempA->next = new ListNode(1);
    tempA = tempA->next;
    tempA->next = new ListNode(8);
    tempA = tempA->next;
    ListNode *temp_cross = tempA;
    tempA->next = new ListNode(4);
    tempA = tempA->next;
    ListNode *headB = new ListNode(5);
    ListNode *tempB = headB;
    tempB->next = new ListNode(6);
    tempB = tempB->next;
    tempB->next = new ListNode(1);
    tempB = tempB->next;
    tempB->next = temp_cross;
    ListNode *test = headA;

    Solution solu;
    cout << solu.getIntersectionNode(headA, headB)->val << endl;
    return 0;
}