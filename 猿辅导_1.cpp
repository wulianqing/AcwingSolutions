#include<iostream>
using namespace std;

struct listNode{
    int data = 0;
    listNode *next = nullptr;
    listNode(int x) { data = x; }
};


int main(){

    //build a list
    int list_length;
    cin >> list_length;
    listNode *head = nullptr;
    listNode *temp = nullptr;
    for (int i = 0; i < list_length; i++){
         int cur_node;
            cin >> cur_node;
        if(head == nullptr){
           
            temp = new listNode(cur_node);
            head = temp;
        }
        else {
            temp->next = new listNode(cur_node);
            temp = temp->next;
        }
    }

    //test list
    cout << "before: ";
    temp = head;
    while(temp->next != nullptr){
        cout << temp->data << "->";
        temp = temp->next;
    }
    cout<< temp->data << endl;

    //reverse
    listNode *reversed_list = nullptr;
    temp = nullptr;
    while (head != nullptr){
        temp = head;
        head = head->next;
        temp->next = reversed_list;
        reversed_list = temp;
    }

    //calculate
    int carry = 0;
    temp = reversed_list;
    while(temp->next != nullptr){
        //the first one
        if(temp == reversed_list){
            if(temp->data + 1 == 10){
                carry = 1;
                temp->data = 0;
            }
            else
                temp->data++;
            temp = temp->next;
            continue;
        }
        if(carry == 1){
            if(temp->data + 1 == 10){
                temp->data = 0;
                carry = 1;
            }
            else
                carry = 0;
        }
        temp = temp->next;
    }
    //exception: end,if carry == 1
    if(carry == 1)
        temp->next = new listNode(1);

    //reverse
    listNode *recover_list = nullptr;
    temp = nullptr;
    while (reversed_list != nullptr){
        temp = reversed_list;
        reversed_list = reversed_list->next;
        temp->next = recover_list;
        recover_list = temp;
    }

    //test list
    cout << "after: ";
    temp = recover_list;
    while(temp->next != nullptr){
        cout << temp->data << "->";
        temp = temp->next;
    }
    cout<< temp->data << endl;
    return 0;
}