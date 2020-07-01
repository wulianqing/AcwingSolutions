#include<iostream>
using std::cin;
using std::cout;
using std::endl;

int main(){
    
    int length_seq;
    cin >> length_seq;
    //exception
    if(length_seq == 1){
        int seq_1;
        cin >> seq_1;
        cout << "max length: " << 1 << endl;
        return 0;
    }
    if(length_seq < 1){
        cout << "error: length of sequence should >= 1." << endl;
        return 0;
    }

    //init
    int *seq = new int[length_seq];
    int dp[length_seq];
    for (int i = 0; i < length_seq;i++){
        dp[i] = 1;
    }

    for (int i = 0; i < length_seq; i++)
    {
        cin >> seq[i];       
    }

    //calculate dp[i] from low to high
    int max_length = 0;
    for (int i = 1; i < length_seq;i++){
        for (int j = i - 1; j >= 0;j--){
            if(seq[j] <= seq[i]){
                if(dp[j]>=dp[i]){
                    dp[i] = dp[j] + 1;
                    if(dp[i] > max_length){
                        max_length = dp[i];
                    }
                }
            }
        }
    }

    //checkout
    cout << "max length: " << max_length << endl;

    return 0;
}