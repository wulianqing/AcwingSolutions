#include<iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //当前进位, 下一位进位
        int carry = 0;
        //两个指针
        ListNode *p1 = l1;
        ListNode *p2 = l2;
        while(p1 != NULL && p2 != NULL){
            int temp = l1->val + l2->val + carry;
            carry = temp / 10;
            l1->val = temp % 10;
            l2->val = temp % 10;
            p1 = p1->next;
            p2 = p2->next;
        }
        //p1 == NULL && p2 == NULL
        if(!(p1 || p2)){
            if(carry != 0){
                p1 = new ListNode(carry);
                return l1;
            }
            else
                return l1;
        }
        //p1 == NULL || p2 == NULL
        if(p1 != NULL){
            p1->val += carry;
            return l1;
        }
        else{
            p2->val += carry;
            return l2;
        }
    }
};
int main(){
    ListNode *l1;
    ListNode *l2;
}