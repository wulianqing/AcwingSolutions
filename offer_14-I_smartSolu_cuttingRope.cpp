#include<iostream>
#include<cmath>
using std::cin;
using std::cout;
using std::endl;

int main(){
    int length_rope;
    cin >> length_rope;
    
    //exception: length_rope == 2 or 3 or <2
    if(length_rope == 2){
        cout << "max product: " << 1 << endl;
        return 0;
    }
    else if(length_rope == 3){
        cout << "max product: " << 2 << endl;
        return 0;
    }
    else if(length_rope <2){
        cout << "error: length of rope should >=2." << endl;
        return 0;
    }

    /*  3 situations: %3 == 0 or 1 or 2
    == 0 : 3*3*...
    == 1 : 3*3*...*2*2
    == 2 : 3*3*3...3*2
    */
    if(length_rope%3 == 0)
        cout << "max product: " << pow(3, length_rope / 3)<<endl;
    else if(length_rope%3 == 1)
        cout << "max product: " << pow(3, length_rope / 3 - 1) * 4 << endl;
    else if(length_rope%3 ==2)
        cout << "max product: " << pow(3, length_rope / 3 ) * 2 << endl;
    return 0;
}