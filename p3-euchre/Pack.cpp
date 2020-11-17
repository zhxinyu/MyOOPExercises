#include "Pack.h"
#include <cassert>
Pack::Pack(): next(0) {
    for (int iter_suit=0;iter_suit<4;iter_suit++)
    {
        for (int iter_rank=0;iter_rank<6;iter_rank++)
    cards[iter_suit*6+iter_rank] =Card(RANK_NAMES_BY_WEIGHT[iter_rank+7],SUIT_NAMES_BY_WEIGHT[iter_suit]);
    }
}
Pack::Pack(std::istream& pack_input): next(0){
    std::string suit;
    std::string rank;
    std::string proposition;
    for (int iter=0;iter<24;iter++)
    {   pack_input>>rank;
        pack_input>>proposition;
        pack_input>>suit;
        cards[iter] = Card(rank,suit);
    }
}

Card Pack::deal_one(){
    assert(next<=23);
    next = next+1;
    return cards[next-1];
    
}

void Pack::reset(){
    next = 0;
}

void Pack::shuffle(){
    std::array<Card,PACK_SIZE> tmp;
    for(int iter=0;iter<7;iter++)
    {
        tmp = cards;
        for (int shuff_iter=0;shuff_iter<PACK_SIZE/2;shuff_iter++)
        {
            cards[shuff_iter*2] = tmp[shuff_iter+PACK_SIZE/2];
            cards[shuff_iter*2+1] = tmp[shuff_iter];
        }
    }
    // for (int iter =0;iter<24;iter++){std::cout<<cards[iter].get_rank()<<" of "<<cards[iter].get_suit()<<std::endl;}
}

bool Pack::empty() const{
    return (next>=24);
}
