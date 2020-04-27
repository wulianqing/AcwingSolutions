#include<iostream>
using namespace std;
int main(){
    string s;
    cout<<"输入字符串"<<endl;
    while(cin>>s){
            int right = s.size()-1;
    int left;
    while(right>=0 && left>=0){
        //右指针是大写：跳过
        if(s[right]>='A'&&s[right]<='Z'){
            right--;
            continue;
        }
        //右指针不是大写：左指针找有没有大写可以扔到后面
        else{
            left = right;
            //
            while(left>=0){
                //左指针找到了大写：交换左右指针元素，再把左指针的小写放到正确位置
                if(s[left]>='A' && s[left]<='Z'){
                    swap(s[left],s[right]);
                    if(right-left == 1){
                        right--;
                        break;
                    }
                    for(int i = left;i<right-1;i++){
                        swap(s[i],s[i+1]);
                    }
                    right--;
                    break;
                }
                else left--;
            }
        }
        //right--;
    }
    cout<<s<<endl;
    }
    return 0;
}