#include<iostream>
using std::cin;
using std::cout;
using std::endl;

struct ListNode{
    int data;
    ListNode *next;
    ListNode(int x=0):data(x),next(nullptr){}
};

int main(){
    ListNode *head = new ListNode;
    int nums[10]={1,2,3,4,5,6,7,8,9,10};
    //init list
    ListNode *temp_head = head;
    for (int i = 0; i < 10; i++)
    {
        ListNode *temp = new ListNode(nums[i]);
        temp_head->next = temp;
        temp_head = temp_head->next;
    }
    //print list
    for (ListNode *temp = head->next; temp != nullptr;temp=temp->next){
        cout << temp->data << " ";
    }
    cout << endl;

    //find the last n element
    cout << "input the last n element u wanna find" << endl;
    int last_n;
    cin >> last_n;
    ListNode *left = head->next;
    ListNode *right = left;
    for (int i = 0; i < last_n; i++)
    {
        if (right->next == nullptr){
            cout << "not exist" << endl;
        }
        else{
            right = right->next;
        }
    }
    while(right != nullptr){
        left = left->next;
        right = right->next;
    }
    cout << "last n element:\t" << left->data << endl;
    return 0;
}