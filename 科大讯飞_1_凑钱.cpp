#include<iostream>
#include<vector>
using namespace std;
void find(vector<int> & v,int & target,int & used){
    //100
    if(target >= 100 && v[4] > 0){
        v[4]--;
        target -= 100;
        used++;
        find(v, target, used);
    }
    //50
    else if(target >= 50 && v[3] > 0){
        v[3]--;
        target -= 50;
        used++;
        find(v, target, used);
    }
    //10
    else if(target >= 10 && v[2] > 0){
        v[2]--;
        target -= 10;
        used++;
        find(v, target, used);
    }
    //5
    else if(target >= 5 && v[1] > 0){
        v[1]--;
        target -= 5;
        used++;
        find(v, target, used);
    }
    //1
    else if(target >= 1 && v[0] > 0){
        v[0]--;
        target -= 1;
        used++;
        find(v, target, used);
    }
    //终止条件
    if(target > 0){
        used = 0;
        return;
    }
        
    
}
int main(){
    vector<int> v(5);
    int max_money;
    for (int i = 0; i < 5; i++){
        cin >> v[i];
    }
    max_money = v[0] + v[1] * 5 + v[2] * 10 + v[3] * 50 + v[4] * 100;
    int target;
    int used = 0;
    cin >> target;
    if(target == 0){
        cout << 0 << endl;
        return 0;
    }
    else if(target > max_money){
        cout << -1 << endl;
        return 0;
    }
    find(v, target, used);
    if(used == 0)
        cout << -1 << endl;
    else
        cout << used << endl;
    return 0;
}