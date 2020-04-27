#include<iostream>
#include<math.h>
using namespace std;
//x在哪行
int xRow(int x){
    int i = 1;
    while (i++){
        if(x>pow(2,i-1)&&x<pow(2,i)-1)
            return i;
    }
}
//x排在它所在行第几个
int xRowSeq(int x){
    
}
int main(){

}