#include<iostream>
using namespace std;

struct listNode{
    int data = 0;
    listNode *next = nullptr;
};

int main(){
    //build a list
    listNode* head = new listNode;
    listNode* cur_ptr = head;
    for (int i = 1; i <= 5; i++)
    {
        listNode *temp = new listNode;
        temp->data = i;
        cur_ptr->next = temp;
        cur_ptr = temp;
    }
   
    //reverse list
    //exception: size <= 1

    //size >= 2
    cur_ptr = head->next->next;
    head->next->next = nullptr;
    for (; cur_ptr != nullptr;)
    {
        listNode *temp = cur_ptr;
        cur_ptr = cur_ptr->next;
        temp->next = head->next;
        head->next = temp;
    }
     //test list
    
    for (listNode *cur = head->next; cur != nullptr; cur = cur->next){
        cout << cur->data << " ";
    }
    cout << endl;
    return 0;
}