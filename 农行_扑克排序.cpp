#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>

std::unordered_map<char, int> ump;
        
void init_ump(){
    ump.insert(std::make_pair('k', 5));
    ump.insert(std::make_pair('s', 4));
    ump.insert(std::make_pair('h', 3));
    ump.insert(std::make_pair('p', 2));
    ump.insert(std::make_pair('q', 1));
}

bool cmp(std::string & a, std::string & b)
{
    char a_suit = a[0];
    char b_suit = b[0];
    int a_num = stoi(a.substr(1));
    int b_num = stoi(b.substr(1));

    if (a_suit == b_suit)
        return a_num < b_num;
    else
        return ump[a_suit] > ump[b_suit];
}

class Solution{
    public:
        std::vector<std::string> getPokerOrder(std::vector<std::string> cards){
            init_ump();
            sort(cards.begin(), cards.end(), cmp);
            return cards;
        }
};

int main(){
    init_ump();
    Solution solu;
    std::vector<std::string> cards = {"s3", "h5", "s9", "k1", "p4", "p1", "q6", "k2"};
    std::vector<std::string>ordered_cards = solu.getPokerOrder(cards);
    for (int i = 0; i < ordered_cards.size();i++)
        std::cout << ordered_cards[i] << std::endl;    
    return 0;
}