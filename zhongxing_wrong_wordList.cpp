// INCLUDE HEADER FILES NEEDED BY YOUR PROGRAM
// SOME LIBRARY FUNCTIONALITY MAY BE RESTRICTED
// DEFINE ANY FUNCTION NEEDED
// FUNCTION SIGNATURE BEGINS, THIS FUNCTION IS REQUIRED
#include<iostream>
using std::cin;
using std::cout;

using namespace std;
int canArrangeWords(int num, char** arr)
{
    // WRITE YOUR CODE HERE
    char* first_letter = new char[num];
    for(int i=0;i<num;i++){
        first_letter[i] = arr[i][0];
        //cout<<first_letter[i]<<" ";
    }
    //cout<<endl;
    char* last_letter = new char[num];
    for(int i=0;i<num;i++){
        last_letter[i] = arr[i][strlen(arr[i])-1];
        //cout<<last_letter[i]<<" ";
    }
    //cout<<endl;
    //travel
    for(int i=0;i<num;i++){
        int cur_found = 0;
        int not_found_counter = 0;
        for (int j = 0; j < num; j++)
        {
            if(first_letter[i] == last_letter[j]){
                cur_found = 1;
            }
        }
        if(cur_found == 0){
            if(not_found_counter == 0){
                not_found_counter++;
            }
            else{
                return -1;
            }
        }
    }
    return 1;
}
// FUNCTION SIGNATURE ENDS