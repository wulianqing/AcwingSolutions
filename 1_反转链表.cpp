#include<iostream>
using namespace std;

struct listNode{
    int data = 0;
    listNode *next = nullptr;
    listNode(int x) { data = x; }
};

int main(){
    //build a list
    listNode *head = nullptr;
    listNode *temp = nullptr;
    for (int i = 1; i <= 10; i++){
        if(head == nullptr){
            temp = new listNode(i);
            head = temp;
        }
        else {
            temp->next = new listNode(i);
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

    cout << temp->data << endl;
    //reserve
    listNode *my_list = nullptr;
    temp = nullptr;
    while (head != nullptr){
        temp = head;
        head = head->next;
        temp->next = my_list;
        my_list = temp;
    }

    //test list
    cout << "reversed: ";
    temp = my_list;
    while(temp->next != nullptr){
        cout << temp->data << "->";
        temp = temp->next;
    }
    cout << temp->data << endl;
    return 0;
}