#include "Player.h"
#include <cassert>
#include <iostream>
#include <algorithm>
//void Player

class SimplePlayer: public Player{
public:
    SimplePlayer(): size(0){}
    SimplePlayer(std::string  NAME):size(0){
        name=NAME;
    }

//    SimplePlayer(std::string &NAME): size(0),round(1){
//        name=NAME;
    //        size = 0;
//        round = 1;
//    }
    const std::string & get_name() const{
        return name;
    }
    void add_card(const Card &c){
        assert(size<=MAX_HAND_SIZE);
        hand.push_back(c);
        size = size+1;
    }
    bool make_trump(const Card &upcard,bool is_dealer,int round,
                    std::string &order_up_suit) const{
        //assert it is round 1 or 2.
        assert(round<=2);
        assert(size==5);
        int count = 0;
        if (round ==1){
            for (int iter=0;iter<MAX_HAND_SIZE;iter++){
                if (hand[iter].is_trump(upcard.get_suit())&hand[iter].is_face()){
                    count++;}
                
            }
            if (count>=2) {
                return true;}
        }
        else {
            count = 0;
            if (is_dealer){
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            for (int iter=0;iter<MAX_HAND_SIZE;iter++){
                if (hand[iter].is_trump(Suit_next(upcard.get_suit()))&hand[iter].is_face()){
                    count++;}
                if (count>=1) {
                    order_up_suit = Suit_next(upcard.get_suit());
                    return true;}
            }
        }
        return false;
    }
    void add_and_discard(const Card &upcard){
        assert(size==5);
        Card tmp = upcard;
        Card min = tmp;
        const std::string trump=upcard.get_suit();
        for (int iter=0;iter<size;iter++){
            if (Card_less(hand[iter],min,trump)){
                tmp  = hand[iter];
                hand[iter] = min;
                min = tmp;}
            }
        }
            
     Card lead_card(const std::string &trump){
         assert(size>=1);
         assert((trump == Card::SUIT_SPADES) |(trump == Card::SUIT_HEARTS)| (trump == Card::SUIT_CLUBS)|(trump == Card::SUIT_DIAMONDS));
         std::vector<int> non_trump_vec;
         for (int iter=1;iter<=size;iter++){
             if (!hand[iter-1].is_trump(trump)){
                 non_trump_vec.push_back(iter);}
         }
         Card tmp;
         int idx;
//         std::cout<<non_trump_vec.size()<<std::endl;
//         assert(false);
         if (non_trump_vec.size()>=1){
             for (auto iter = non_trump_vec.cbegin();iter!=non_trump_vec.cend();iter++){
                 if (iter==non_trump_vec.cbegin()){
                     tmp = hand[*iter-1];
                     idx = *iter-1;
                     
                 }
                 else {if (Card_less(tmp,hand[*iter-1],trump)) {
                     tmp = hand[*iter-1];
                     idx = *iter-1;
                 }
                 }
             }
             // for (int iter=idx+1;iter<size;iter++){
             //     hand[iter-1]=hand[iter];
             // }
             size = size-1;
             hand.erase(hand.cbegin()+idx);
//             hand.resize(size);
             return tmp;
         }
         else{
             for (int iter=0;iter<size;iter++){
                 if (iter==0){
                 tmp = hand[0];
                 idx =  iter;}
             else {
                 if (Card_less(tmp,hand[iter],trump)) {
                     tmp =hand[iter];
                     idx = iter;
                 }
             }
                 }
             // for (int iter=idx+1;iter<size;iter++){
             //     hand[iter-1]=hand[iter];
             // }
             size = size-1;
             hand.erase(hand.cbegin()+idx);
//             hand.resize(size);
             return tmp;
                     
         }
                }
    Card play_card(const Card &led_card,const std::string &trump){
        assert(size>=1);
        assert((trump == Card::SUIT_SPADES) |(trump == Card::SUIT_HEARTS)| (trump == Card::SUIT_CLUBS)|(trump == Card::SUIT_DIAMONDS));
        Card tmp;
        int idx;
        std::vector<int> lead_vec;
        for (int iter=1;iter<=size;iter++){
            if (hand[iter-1].get_suit(trump)==led_card.get_suit(trump)){
                lead_vec.push_back(iter);}
        }
        if (lead_vec.size()>=1){
            // if (name=="Gabriel")
            // {std::cout<<lead_vec.size()<<std::endl;}
            for (auto iter = lead_vec.cbegin();iter!=lead_vec.cend();iter++){
                if (iter==lead_vec.cbegin()){
                    tmp = hand[*iter-1];
                    idx = *iter-1;
                }
                else {if (Card_less(tmp,hand[*iter-1],led_card,trump)) {
                    tmp = hand[*iter-1];
                    idx = *iter-1;
                }
                }
            }
            // for (int iter=idx+1;iter<size;iter++){
            //     hand[iter-1]=hand[iter];
            // }
            hand.erase(hand.cbegin()+idx);
            size = size-1;
            // hand.resize(size);
            return tmp;
        }
        else{
            for (int iter=0;iter<size;iter++){
                if (iter==0){
                    tmp = hand[0];
                    idx =  iter;}
                else {
                    if (Card_less(hand[iter],tmp,led_card,trump)) {
                        tmp =hand[iter];
                        idx = iter;
                    }
                }
            }
            // for (int iter=idx+1;iter<size;iter++){
            //     hand[iter-1]=hand[iter];
            // }
            size = size-1;
            // hand.resize(size);
            hand.erase(hand.cbegin()+idx);
            return tmp;
            
        }

    }
    //~SimplePlayer();
    ~SimplePlayer(){};
private:
    std::vector<Card> hand;
    int size;
    std::string name = "Simple";
};

class HumanPlayer:public Player{
public:
    HumanPlayer(): size(0){}
    HumanPlayer(std::istream &is): size(0){
        is>>name;
    }
    HumanPlayer(std::string NAME): size(0){
        name=NAME;
    }
    const std::string & get_name() const{
        return name;
    }
    void add_card(const Card& c){
        assert(size<=MAX_HAND_SIZE);
        hand.push_back(c);
        size = size+1;
        if (hand.size()==MAX_HAND_SIZE){
            std::sort(hand.begin(),hand.end());
        }
    }
    bool make_trump(const Card &upcard,bool is_dealer,int round,std::string &order_up_suit) const{
        std::string decision;
        for (auto iter=hand.cbegin();iter!=hand.cend();iter++){
            std::cout<<"Human player "<<name+"'s hand: "<<"["<<iter-hand.cbegin()<<"] "<<(*iter).get_rank() <<" of "<<(*iter).get_suit()<<std::endl;
        }
        std::cout<<"Human player "<<name+", please enter a suit, or \"pass\":"<<std::endl;
        std::cin>>decision;
        assert((decision=="pass")|(decision=="Spades")|(decision=="Hearts")|(decision=="Clubs")|(decision=="Diamonds"));
//        if (decision=="pass")
//        {std::cout<<name<<" passes"<<std::endl;}
//        else {
//            std::cout<<name<<" orders up"<<decision<<std::endl;
//        }

        if (decision=="pass"){
            return false;
        }
        else{
            order_up_suit = decision;
            return true;
        }
    }
    void add_and_discard(const Card& upcard){
        int idx;
        assert(size==5);
        std::sort(hand.begin(),hand.end());
        for (auto iter=hand.cbegin();iter!=hand.cend();iter++){
            std::cout<<"Human player "+name<<"'s hand: "<<"["<<iter-hand.cbegin()<<"] "<<(*iter).get_rank() <<" of "<<(*iter).get_suit()<<std::endl;
        }
        std::cout<<"Discard upcard: [-1]"<<std::endl;
        std::cout<<"Human player "<<name<<", please select a card to discard:"<<std::endl;
        //std::cout<<upcard.get_rank()<<" of "<<upcard.get_suit()<<std::endl;
        std::cin>>idx;
        assert((idx>=-1)&(idx<=size-1));
        if (idx>=0){
            hand[idx]=upcard;
        }
    }
    
    Card lead_card(const std::string &trump){
        int idx;
        Card tmp;
        assert((size>=1) &(size<=5));
        std::sort(hand.begin(),hand.end());
        for (auto iter=hand.cbegin();iter!=hand.cend();iter++){
            std::cout<<"Human player "+name<<"'s hand: "<<"["<<iter-hand.cbegin()<<"] "<<(*iter).get_rank() <<" of "<<(*iter).get_suit()<<std::endl;
        }
        std::cout<<"Human player "<<name<<", please select a card:"<<std::endl;
        std::cin>>idx;
        assert((idx>=0)&(idx<=size-1));
        size = size-1;
        tmp = hand[idx];
//        std::cout<<tmp.get_rank()<<" of "<<tmp.get_suit()<<" led by "<<name<<std::endl;
        hand.erase(hand.begin()+idx);
        //hand.resize(size);
        return tmp;
        
    }
    Card play_card(const Card &led_card,const std::string &trump){
        int idx;
        Card tmp;
        std::sort(hand.begin(),hand.end());
        for (auto iter=hand.cbegin();iter!=hand.cend();iter++){
            std::cout<<"Human player "+name<<"'s hand: "<<"["<<iter-hand.cbegin()<<"] "<<(*iter).get_rank() <<" of "<<(*iter).get_suit()<<std::endl;
        }
        std::cout<<"Human player "<<name<<", please select a card:"<<std::endl;
        std::cin>>idx;
        assert((idx>=0)&(idx<=size-1));
        size = size-1;
        tmp =hand[idx];
//        std::cout<<tmp.get_rank()<<" of "<<tmp.get_suit()<<" played by "<<name<<std::endl;
        //hand.resize(size);
        hand.erase(hand.begin()+idx);
        return tmp;
    }
    ~HumanPlayer(){};
    
private:
    std::vector<Card> hand;
    int size;
    std::string name = "Human";
};

Player * Player_factory(const std::string &name,const std::string &strategy){
    if (strategy=="Simple"){
        return new SimplePlayer(name);
    }
    else if (strategy=="Human"){
            return new HumanPlayer(name);
        }
    assert(false);
    return nullptr;}

std::ostream & operator<<(std::ostream &os,const Player &p){
    os<<p.get_name();
    return os;
}
