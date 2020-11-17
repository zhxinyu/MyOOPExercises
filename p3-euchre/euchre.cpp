#include "Player.h"
#include "Pack.h"
#include <fstream>
#include <stdlib.h>
class Game{
public:
    Game(){};
    
    void get_pack(Pack & PACK){
         pack = PACK;
    }
    std::vector<int> get_scores() const{
        return scores;
    }
    void add_player(const std::string &name,const std::string &strategy){
        players.push_back(Player_factory(name,strategy));
        //std::cout<<"Add player successful!"<<std::endl;
    }
    Player * get_player(int idx ) const{
        return players[idx];
    }
    void deal_card(int hand){
        for (int iter=0;iter<3;iter++)
        {players[(hand+1)%4]->add_card(pack.deal_one());}
        for (int iter=0;iter<2;iter++)
        {players[(hand+2)%4]->add_card(pack.deal_one());}
        for (int iter=0;iter<3;iter++)
        {players[(hand+3)%4]->add_card(pack.deal_one());}
        for (int iter=0;iter<2;iter++)
        {players[(hand)%4]->add_card(pack.deal_one());}
        for (int iter=0;iter<2;iter++)
        {players[(hand+1)%4]->add_card(pack.deal_one());}
        for (int iter=0;iter<3;iter++)
        {players[(hand+2)%4]->add_card(pack.deal_one());}
        for (int iter=0;iter<2;iter++)
        {players[(hand+3)%4]->add_card(pack.deal_one());}
        for (int iter=0;iter<3;iter++)
        {players[(hand)%4]->add_card(pack.deal_one());}
    }
//    std::string make_trump(int hand){
//    }
    
    void trump_lead_play_trick(int hand){
        
        Card upcard = pack.deal_one();
        std::string trump;
        int trump_side;
        std::string order_up_suit = upcard.get_suit();
        std::cout<<upcard.get_rank()<<" of "<<upcard.get_suit()<<" turned up"<<std::endl;
        int round = 1;
        bool trump_flag = false;
        for (int iter=1;iter<=4;iter++)
        {
            if (players[(hand+iter)%4]->make_trump(upcard,(bool)(iter==4),round,order_up_suit)){
                std::cout<<*(players[(hand+iter)%4])<<" orders up "<<order_up_suit<<std::endl;
                players[(hand%4)]->add_and_discard(upcard);
                std::cout<<std::endl;
                trump = order_up_suit;
                trump_side = (hand+iter)%2;
                trump_flag = true;
                break;
            }
            else{
                std::cout<<*(players[(hand+iter)%4])<<" passes"<<std::endl;
                continue;
            }
        }
        if (!trump_flag){
        round++;
        for (int iter=1;iter<=4;iter++)
        {
            if (players[(hand+iter)%4]->make_trump(upcard,(bool)(iter==4),round,order_up_suit)){
                std::cout<<*(players[(hand+iter)%4])<<" orders up "<<order_up_suit<<std::endl<<std::endl;
                trump = order_up_suit;
                trump_side = (hand+iter)%2;
                break;
            }
            else{
                std::cout<<*(players[(hand+iter)%4])<<" passes"<<std::endl;
                continue;
            }
        }}

        
        int str_idx =hand+1;
        int idx = hand+1;
        std::vector<int> hand_pt{0,0};
        for (int iter=0;iter<5;iter++){
            Card led_card = players[(str_idx)%4]->lead_card(trump);
            std::cout<<led_card.get_rank()<<" of "<<led_card.get_suit()<<" led by "<<*(players[(str_idx)%4])<<std::endl;
            Card trick_card = led_card;

            Card played_card = players[(str_idx+1)%4]->play_card(led_card,trump);
            std::cout<<played_card.get_rank()<<" of "<<played_card.get_suit()<<" played by "<<*(players[(str_idx+1)%4])<<std::endl;
            if (Card_less(trick_card,played_card,led_card,trump)){
                trick_card = played_card;
                idx = str_idx+1;
            }
            
            played_card = players[(str_idx+2)%4]->play_card(led_card,trump);
            std::cout<<played_card.get_rank()<<" of "<<played_card.get_suit()<<" played by "<<*(players[(str_idx+2)%4])<<std::endl;
            if (Card_less(trick_card,played_card,led_card,trump)) {
                trick_card =played_card;
                idx = str_idx+2;
            }
            
            played_card = players[(str_idx+3)%4]->play_card(led_card,trump);
            std::cout<<played_card.get_rank()<<" of "<<played_card.get_suit()<<" played by "<<*(players[(str_idx+3)%4])<<std::endl;
            if (Card_less(trick_card,played_card,led_card,trump)) {
                trick_card =played_card;
                idx = str_idx+3;
            }
            std::cout<<*(players[(idx)%4])<<" takes the trick"<<std::endl<<std::endl;
            hand_pt[idx%2] +=1;
            str_idx = idx;
        }
        //scores[0] = hand_pt[0];
        //scores[1] = hand_pt[1];
        if (hand_pt[0]>hand_pt[1]){
            std::cout<<*(players[0])<<" and "<<*(players[2])<<" win the hand"<<std::endl;
            if ((hand_pt[0]==5)&(trump_side==0)){
                scores[0]+=2;
                std::cout<<"march!"<<std::endl;
                
            }
            if ((hand_pt[0]<5)&(trump_side==0)){
                scores[0]+=1;
            }
            if (trump_side==1){
                std::cout<<"euchred!"<<std::endl;
                scores[0]+=2;
            }
        }
        else{
            std::cout<<*(players[1])<<" and "<<*(players[3])<<" win the hand"<<std::endl;
            if ((hand_pt[1]==5)&(trump_side==1)){
                scores[1]+=2;
                std::cout<<"march!"<<std::endl;
                
            }
            if ((hand_pt[1]<5)&(trump_side==1)){
                scores[1]+=1;
            }
            if (trump_side==0){
                std::cout<<"euchred!"<<std::endl;
                scores[1]+=2;
            }
            
        }
            std::cout<<*(players[0])<<" and "<<*(players[2])<<" have "<<scores[0]<<" points"<<std::endl;
            std::cout<<*(players[1])<<" and "<<*(players[3])<<" have "<<scores[1]<<" points"<<std::endl<<std::endl;

    }
    //void play_trick(int hand,const std::string &trump)

    
    
    ~Game(){
        for (int i = 0;i<int(players.size());i++){
            delete players[i];
        }
    };
private:
    std::vector<Player *> players;
    Pack pack;
    std::vector<int> scores{0,0};
};

void print_arg(int argc, char *argv[]){
    for (int iter=0;iter<argc;iter++){
        std::cout<<argv[iter]<<" ";
    }
    std::cout<<std::endl;
    
}

bool check_arg(int argc, char *argv[]){
    bool output = true;
    char *p;
    output = output*(argc==12);
    output = output*(strcmp(argv[0],"./euchre.exe")==0);
    int score2win = strtol(argv[3],&p,10);
    output = output*((score2win>=1)&(score2win<=100));
    output*=((strcmp(argv[2],"shuffle")==0)|(strcmp(argv[2],"noshuffle")==0));
    output*=( ((strcmp(argv[5],"Simple")==0)|(strcmp(argv[5],"Human")==0))&((strcmp(argv[7],"Simple")==0)|(strcmp(argv[7],"Human")==0))&((strcmp(argv[9],"Simple")==0)|(strcmp(argv[9],"Human")==0))&((strcmp(argv[11],"Simple")==0)|(strcmp(argv[11],"Human")==0)));
    if (!output){
        std::cout<<"Usage: euchre.exe PACK_FILENAME [SHUFFLE|NONSHUFFLE] "<<"POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4"<<std::endl;
        return false;
    }
    return true;
}

int main(int argc,char *argv[]){
    if (!check_arg(argc,argv)){
        return 1;
    };
    char *p;
    print_arg(argc, argv);
    int score2win = strtol(argv[3],&p,10);
    const std::string filename = argv[1];
    std::ifstream ifs(filename);
    //std::cout<<ifs.rdbuf()<<std::endl;
    if (!ifs.is_open()){
        std::cout<<"Error opening "<<filename<<std::endl;
    }
    Game game;
    game.add_player(argv[4],argv[5]);
    game.add_player(argv[6],argv[7]);
    game.add_player(argv[8],argv[9]);
    game.add_player(argv[10],argv[11]);
    bool shuffle = (strcmp(argv[2],"shuffle")==0);
    Pack pack(ifs);
    if (shuffle){
            pack.shuffle();
    }

    //std::cout<<(game.get_scores()[0]<score2win)&(game.get_scores()[1]<score2win)<<std::endl;
    int hand = 0;
    while ((game.get_scores()[0]<score2win)&(game.get_scores()[1]<score2win)){
        if (shuffle& (hand>=1)){
                pack.shuffle();}
        game.get_pack(pack);
        game.deal_card(hand);
        std::cout<<"Hand "<<hand<<std::endl;
        std::cout<<*(game.get_player((hand%4)))<<" deals"<<std::endl;
        game.trump_lead_play_trick(hand);
        hand++;
    }
    
    if (game.get_scores()[0]>game.get_scores()[1]){
        std::cout<<*(game.get_player(0))<<" and "<<*(game.get_player(2))<<" win!"<<std::endl;
    }
    else {
        std::cout<<*(game.get_player(1))<<" and "<<*(game.get_player(3))<<" win!"<<std::endl;
    }

    
    

    return 0;
}
