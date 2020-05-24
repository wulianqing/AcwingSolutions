#include<iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
    /*
    init 2 strings
    resouce_str, target_str
    */
    string resouce_str;
    string target_str;
    cout << "input resouec string and target string" << endl;
    cin >> resouce_str >> target_str;
    int length_res_str = resouce_str.size();
    int length_tar_str = target_str.size();

    //exception: length of string is 0 or 1


    //build dp table
    int **dp_table = new int *[length_res_str + 1]; //+1: store empty string ""
    for (int i = 0; i < length_res_str + 1;i++){
        dp_table[i] = new int[length_tar_str + 1];
    }

    //init dp table: 1st row and 1st col
    //1st row
    for (int i = 0; i < length_tar_str + 1;i++){
        dp_table[0][i] = i;
    }
    //1st col
    for (int i = 0; i < length_res_str + 1;i++){
        dp_table[i][0] = i;
    }

    /*
    calculate dp table
    1. resouce_str[i] == target_str[j]
    2. resouce_str[i] != target_str[j]: min(3 situations)
    */
    for (int i = 1; i < length_res_str + 1;i++){
        for (int j = 1; j < length_tar_str + 1;j++){
            if(resouce_str[i-1] == target_str[j-1]){
                dp_table[i][j] = dp_table[i - 1][j - 1];
                //cout << "i:" << i << " j:" << j << "\t\t" << dp_table[i][j] << endl;
            }
            else{
                dp_table[i][j] = std::min(dp_table[i - 1][j - 1] + 1, \
                std::min(dp_table[i - 1][j] + 1, dp_table[i][j - 1] + 1));
                //cout << "i:" << i << " j:" << j << "\t\t" << dp_table[i][j] << endl;
            }
        }
    }

    //check out
    cout << "edit distance: " << dp_table[length_res_str][length_tar_str]<<endl;

    return 0;
}