#include<iostream>
#include<list>
using std::cin;
using std::cout;
using std::endl;
using std::list;
int main(){
    list<int> my_list;
    for (int i = 0; i < 10;i++){
        my_list.push_back(i+1);
    }
    for (list<int>::iterator it =my_list.begin(); it != my_list.end();it++){
        cout << *it << " ";
    }
    
    cout << "\ninput n to find the last n number in list" << endl;
    int last_n;
    cin >> last_n;
    list<int>::iterator left, right;
    left = my_list.begin();
    right = my_list.begin();
    for (int i = 0; i < last_n; i++)
    {
        if(right == my_list.end()){
            cout << "not exist." << endl;
            return 0;
        }
        else
            right++;
    }
    while(right != my_list.end()){
        left++;
        right++;
    }
    cout << *left << endl;
    //insert用法 
    my_list.insert(my_list.begin(), -1);
    for (list<int>::iterator it =my_list.begin(); it != my_list.end();it++){
        cout << *it << " ";
    }
    
    return 0;
}
