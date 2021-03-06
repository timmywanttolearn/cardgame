#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include<QMap>
// used to make a class for player
class player
{
private:
    QString name;// the name of the player
    int score;// stores scores for players
    cardHeap playerHeap;//store cards for players
    bool win;// a flag to show whether a palyer wins or not
    bool round;// if it is 1, it is this player has go through this turn
    int num_win_round;//number of wins
public:
    player();
    ~player(){};
    int get_score() const;//used to show this player's score in a turn
    void player_fetchCard(card card_fetched);//get card from card Heap in a game
    QString get_name() const;
    void set_name(QString player_name);
    void set_win(bool a);// a flag to show whether he is winning or not
    void set_round(bool a);// change flag round
    void set_score(int a);
    void init_player();//used to set to next round
    int get_num_cards() const;
    void add_new_win();
    void clear_fetched_cards();
    int get_num_wins() const;
    bool self_judge();

};

class player_uno
{
private:
    bool is_human = true;
    card_uno_heap player_heap;
public:
    QVector<bool> OK_flag;
private:
    QMap<card_uno::COLOR, bool> has_reverse;
    QMap<card_uno::COLOR, bool> has_skip;
    QMap<card_uno::COLOR, bool> has_draw_two;
    QMap<card_uno::CARD_TYPE, bool> has_wild;
    void set_false();
    card_uno *last_card_given;
public:
    player_uno(bool human);
    bool no_cards_to_give(card_uno *last_card) const;
    card_uno *give_card(card_uno *card);
    void fetch_card(card_uno *card);
    bool win() const{return player_heap.is_empty();}
    void update_card_status(card_uno *last_card);
    int get_current_card_number() const{return player_heap.get_size();}

    //return whether the player have the special card having the given color / type
    bool has_reverse_colored(card_uno::COLOR color) const {return has_reverse[color];}
    bool has_skip_colored(card_uno::COLOR color) const {return has_skip[color];}
    bool has_draw_two_colored(card_uno::COLOR color) const{return has_draw_two[color];}
    bool has_wild_with_type(card_uno::CARD_TYPE type) const{return has_wild[type];}

    //return thr last card given out by the player
    card_uno *get_last_card() const{return last_card_given;}

    //return the pointer to a card at a given position of this player
    card_uno* peek_card(int index) {if(index < player_heap.get_size() && index >= 0) return player_heap[index]; else return nullptr;}
    //return whether the card at the given position is able to be given
    bool check_card(int index) const{if(index < player_heap.get_size() && index >= 0) return OK_flag[index]; else return false;}
    card_uno* ai_chosen(card_uno* lastcard,bool reverse,int drawnum);
};

#endif
