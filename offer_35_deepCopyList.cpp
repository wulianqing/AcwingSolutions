#include<iostream>
#include<map>
using namespace std;
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == NULL)return NULL;
        Node* temp_head = head;
        Node* ans = new Node(temp_head->val);
        //Node* ans = NULL;
        ans->random = NULL;
        Node* cur_ptr = ans;
        map<Node*,Node* > my_map;
        my_map.insert(make_pair(head,cur_ptr));
        temp_head = temp_head->next;
        while(temp_head != NULL){
            Node* temp = new Node(temp_head->val);
            temp->random = NULL;
            cur_ptr->next = temp;
            my_map.insert(make_pair(temp_head,temp));
            temp_head = temp_head->next;
            cur_ptr = cur_ptr->next;
        }
        cur_ptr = ans;
        while(cur_ptr != NULL){
            cur_ptr->random = my_map[head->random];
            cur_ptr = cur_ptr->next;
            head = head->next;
        }
        return ans;
    }
};