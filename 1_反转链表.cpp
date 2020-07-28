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

    //恢复:1~10
    temp = nullptr;
    while (my_list != nullptr){
        temp = my_list;
        my_list = my_list->next;
        temp->next = head;
        head = temp;
    }
    
    //reverse k per group
    //cout << "k = ?" << endl;
    int k = 3;
    int counter = 0; //当counter % k == 0, 将temp_k加入my_k_list,并清空temp_k
    listNode *my_k_list = nullptr;
    listNode *temp_k = nullptr;
    listNode *tail_k_list = nullptr;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        temp->next = temp_k;
        temp_k = temp;
        counter++;
        if(counter % k == 0 || head == nullptr){
            if(my_k_list == nullptr){
                my_k_list = temp_k;
                temp_k = nullptr;
                tail_k_list = my_k_list;
                while(tail_k_list->next != nullptr)
                    tail_k_list = tail_k_list->next;
            }
            else{
                tail_k_list->next = temp_k;
                temp_k = nullptr;
                while(tail_k_list->next != nullptr)
                    tail_k_list = tail_k_list->next;
            }
        }
    }
    //test list
    cout << "reversed k: ";
    temp = my_k_list;
    while(temp->next != nullptr){
        cout << temp->data << "->";
        temp = temp->next;
    }
    cout << temp->data << endl;

    return 0;
}