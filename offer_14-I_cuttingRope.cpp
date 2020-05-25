#include<iostream>
#include<unordered_map>
using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;

int main(){
    //input
    cout << "input the length of rope" << endl;
    int length_rope;
    cin >> length_rope;

    //exception
    if(length_rope < 2)
        cout << "error: length of rope should >= 2." << endl;

    //build dp_memo: unordered_map<pieces, max_product>
    unordered_map<int, int> map_memo;
    
    //init
    int max_product = 0;
    //int pieces_1[(length_rope + 1)/2]; // 11: 3 3 5
    //int pieces_2[(length_rope + 1)/2];// 11: 4 4 3
    

    //calculate dp_memo
    for (int num_pieces = 2; num_pieces <= length_rope/2 + 1; num_pieces++){
        int curr_max_product =0;
        int curr_product_1 = 1;
        int curr_produce_2 = 1;
        int* pieces_1 = new int[num_pieces]; // 11: 3 3 5
        int* pieces_2 = new int [num_pieces];// 11: 4 4 3
        //calculate
        for (int i = 0; i < num_pieces - 1;i++){
            pieces_1[i] = length_rope / num_pieces;
            pieces_2[i] = length_rope / num_pieces + 1;
            curr_product_1 *= pieces_1[i];
            curr_produce_2 *= pieces_2[i];
        }
        pieces_1[num_pieces-1] = length_rope - (num_pieces - 1) * (length_rope / num_pieces);
        curr_product_1 *= pieces_1[num_pieces-1];
        //pieces_2[num_pieces] could be < 0
        pieces_2[num_pieces-1] = length_rope - (num_pieces - 1) * (length_rope / num_pieces + 1);  
        if(pieces_2[num_pieces-1] <= 0){
            curr_produce_2 = 1;
        }
        else 
            curr_produce_2 *= pieces_2[num_pieces - 1];
        
        curr_max_product = std::max(curr_product_1, curr_produce_2);
        map_memo.insert(std::make_pair(num_pieces, curr_max_product));
        if(curr_max_product > max_product)
            max_product = curr_max_product;
    }

    //checkout
    cout << "max product: " << max_product << endl;
    return 0;
}
