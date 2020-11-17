// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
Card::Card(): rank(Card::RANK_TWO),suit(Card::SUIT_SPADES) {}
Card::Card(const std::string &rank_in,const std::string & suit_in): rank(rank_in),suit(suit_in){
}
std::string Card::get_rank() const {
	return rank;
}
std::string Card::get_suit() const{
	return suit;
}
std::string Card::get_suit(const std::string &trump) const{
	assert((trump == SUIT_SPADES) |(trump == SUIT_HEARTS)| (trump == SUIT_CLUBS)|(trump == SUIT_DIAMONDS));
	if ((trump==SUIT_SPADES)&(get_suit()==SUIT_CLUBS)&(get_rank()==RANK_JACK))
		return trump;
	if ((trump==SUIT_CLUBS)&(get_suit()==SUIT_SPADES)&(get_rank()==RANK_JACK))
		return trump;
	if ((trump==SUIT_HEARTS)&(get_suit()==SUIT_DIAMONDS)&(get_rank()==RANK_JACK))
		return trump;
	if ((trump==SUIT_DIAMONDS)&(get_suit()==SUIT_HEARTS)&(get_rank()==RANK_JACK))
		return trump;
	return get_suit();
}

bool Card::is_face() const {
	if ((get_rank()==RANK_JACK)|(get_rank()==RANK_QUEEN)|(get_rank()==RANK_KING)|(get_rank()==RANK_ACE))
		return true;
	else
		return false;
}

bool Card::is_right_bower(const std::string &trump) const{
	assert((trump == SUIT_SPADES) |(trump == SUIT_HEARTS)| (trump == SUIT_CLUBS)|(trump == SUIT_DIAMONDS));
	if ((get_rank()==RANK_JACK)&(get_suit()==trump))
		return true;
	else
		return false;
}
bool Card::is_left_bower(const std::string &trump) const{
	assert((trump == SUIT_SPADES) |(trump == SUIT_HEARTS)| (trump == SUIT_CLUBS)|(trump == SUIT_DIAMONDS));
	if ((trump==SUIT_SPADES)&(get_suit()==SUIT_CLUBS)&(get_rank()==RANK_JACK))
		return true;
	if ((trump==SUIT_CLUBS)&(get_suit()==SUIT_SPADES)&(get_rank()==RANK_JACK))
		return true;
	if ((trump==SUIT_HEARTS)&(get_suit()==SUIT_DIAMONDS)&(get_rank()==RANK_JACK))
		return true;
	if ((trump==SUIT_DIAMONDS)&(get_suit()==SUIT_HEARTS)&(get_rank()==RANK_JACK))
		return true;
	return false;
}

bool Card::is_trump(const std::string &trump) const{
	if (get_suit(trump)==trump)
		return true;
	return false;
}

bool operator<(const Card &lhs, const Card &rhs){
    auto lhs_rank_iter = std::find(RANK_NAMES_BY_WEIGHT,RANK_NAMES_BY_WEIGHT+NUM_RANKS,lhs.get_rank());
    auto rhs_rank_iter = std::find(RANK_NAMES_BY_WEIGHT,RANK_NAMES_BY_WEIGHT+NUM_RANKS,rhs.get_rank());
    if (lhs_rank_iter<rhs_rank_iter){return true;}
    else if (lhs_rank_iter>rhs_rank_iter){return false;}
    else {
        auto lhs_suit_iter = std::find(SUIT_NAMES_BY_WEIGHT,SUIT_NAMES_BY_WEIGHT+NUM_SUITS,lhs.get_suit());
        auto rhs_suit_iter = std::find(SUIT_NAMES_BY_WEIGHT,SUIT_NAMES_BY_WEIGHT+NUM_SUITS,rhs.get_suit());
        if (lhs_suit_iter<rhs_suit_iter){return true;}
        else
            return false;
    }
}

bool operator>(const Card &lhs, const Card &rhs){
    auto lhs_rank_iter = std::find(RANK_NAMES_BY_WEIGHT,RANK_NAMES_BY_WEIGHT+NUM_RANKS,lhs.get_rank());
    auto rhs_rank_iter = std::find(RANK_NAMES_BY_WEIGHT,RANK_NAMES_BY_WEIGHT+NUM_RANKS,rhs.get_rank());
    if (lhs_rank_iter>rhs_rank_iter){return true;}
    else if (lhs_rank_iter<rhs_rank_iter){return false;}
    else {
        auto lhs_suit_iter = std::find(SUIT_NAMES_BY_WEIGHT,SUIT_NAMES_BY_WEIGHT+NUM_SUITS,lhs.get_suit());
        auto rhs_suit_iter = std::find(SUIT_NAMES_BY_WEIGHT,SUIT_NAMES_BY_WEIGHT+NUM_SUITS,rhs.get_suit());
        if (lhs_suit_iter>rhs_suit_iter){return true;}
        else
            return false;
    }
}

bool operator==(const Card &lhs, const Card &rhs){
    auto lhs_rank_iter = std::find(RANK_NAMES_BY_WEIGHT,RANK_NAMES_BY_WEIGHT+NUM_RANKS,lhs.get_rank());
    auto rhs_rank_iter = std::find(RANK_NAMES_BY_WEIGHT,RANK_NAMES_BY_WEIGHT+NUM_RANKS,rhs.get_rank());
    auto lhs_suit_iter = std::find(SUIT_NAMES_BY_WEIGHT,SUIT_NAMES_BY_WEIGHT+NUM_SUITS,lhs.get_suit());
    auto rhs_suit_iter = std::find(SUIT_NAMES_BY_WEIGHT,SUIT_NAMES_BY_WEIGHT+NUM_SUITS,rhs.get_suit());
    if (lhs_rank_iter==rhs_rank_iter){
        if (lhs_suit_iter==rhs_suit_iter){return true;}
    }
    return false;
}

bool operator!=(const Card &lhs, const Card &rhs){
    auto lhs_rank_iter = std::find(RANK_NAMES_BY_WEIGHT,RANK_NAMES_BY_WEIGHT+NUM_RANKS,lhs.get_rank());
    auto rhs_rank_iter = std::find(RANK_NAMES_BY_WEIGHT,RANK_NAMES_BY_WEIGHT+NUM_RANKS,rhs.get_rank());
    auto lhs_suit_iter = std::find(SUIT_NAMES_BY_WEIGHT,SUIT_NAMES_BY_WEIGHT+NUM_SUITS,lhs.get_suit());
    auto rhs_suit_iter = std::find(SUIT_NAMES_BY_WEIGHT,SUIT_NAMES_BY_WEIGHT+NUM_SUITS,rhs.get_suit());
    if (lhs_rank_iter!=rhs_rank_iter){return true;}
    else if (lhs_suit_iter!=rhs_suit_iter){return true;}
    return false;

}

std::string Suit_next(const std::string &suit) {
    assert((suit == Card::SUIT_SPADES) |(suit ==Card:: SUIT_HEARTS)| (suit == Card::SUIT_CLUBS)|(suit == Card::SUIT_DIAMONDS));
    if (suit==Card::SUIT_SPADES)
        return Card::SUIT_CLUBS;
    else if (suit==Card::SUIT_CLUBS)
        return Card::SUIT_SPADES;
    else if (suit==Card::SUIT_HEARTS)
        return Card::SUIT_DIAMONDS;
    else
        return Card::SUIT_HEARTS ;
}


std::ostream & operator<<(std::ostream &os, const Card &card){
    os<<card.get_rank()+" of "+card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const std::string &trump){
    assert((trump == Card::SUIT_SPADES) |(trump == Card::SUIT_HEARTS)| (trump == Card::SUIT_CLUBS)|(trump == Card::SUIT_DIAMONDS));
    if (a.is_trump(trump)){
        if (b.is_trump(trump))
        {
            if (a.is_left_bower(trump)){
                if (b.is_right_bower(trump)) {
                    return true;}
                else
                    return false;
            }
            else if (a.is_right_bower(trump)){return false;}
            
            else if (b.is_left_bower(trump)|b.is_right_bower(trump)) return true;
            
            else return a<b;
        }
            else
                return false;
    }
    else {
        if (b.is_trump(trump))
        {
            return true;
        }
        else
            return a<b;

    }
}


bool Card_less(const Card &a,const Card &b,const Card &led_card,const std::string &trump){
    if (led_card.get_suit(trump)==trump){
        return Card_less(a,b,trump);
    }
    else {
        if (a.is_trump(trump)){
            if (b.is_trump(trump)){
                if (a.is_left_bower(trump)){
                    if (b.is_right_bower(trump)){
                        return true;
                    }
                    else return false;
                }
                else if (a.is_right_bower(trump)) {return false;}
                
                else if (b.is_left_bower(trump)|b.is_right_bower(trump)) return true;
                else return a<b;
            }
            else return false;
        }
        else {
            if (b.is_trump(trump)) return true;
        }
        // now neither a nor b is trump.
        
        if (a.get_suit()==led_card.get_suit()){
            if (b.get_suit()==led_card.get_suit())
                return a<b;
            else return false;
        }
        else {
            if (b.get_suit()==led_card.get_suit())
                return true;
            else return a<b;
        }
    }
}
