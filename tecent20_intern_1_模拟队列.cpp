#include<iostream>
#include<queue>
using namespace std;

int main(){
    int groups;
    //cout << "输入组数" << endl;
    cin >> groups;
    while (groups--){
        int ops;
        //cout << "输入操作数" << endl;
        cin >> ops;
        queue<int> q;
        while(ops--){
            string op;
            //cout << "输入操作符" << endl;
            cin >> op;
            //cout << op << endl;
            if (op == "PUSH")
            {
                int number;
                cin >> number;
                q.push(number);
                //cout << q.front() << endl;
            }
            else if(op=="TOP"){
                if(q.empty()==1)cout << -1 << endl;
                else cout << q.front() << endl;
            }
            else if(op=="POP"){
                if(q.empty()==1)cout << -1 << endl;
                else q.pop();
            }
            else if(op=="SIZE")cout << q.size()<<endl;
            else if(op=="CLEAR"){
                int temp = q.size();
                for (int i = 0; i < temp; i++)
                {
                    q.pop();
                }
            }
        }
        
    }
    return 0;
}